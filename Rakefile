# vim: set filetype=ruby et sw=2 ts=2:

begin
  # require 'rake/gempackagetask'
  require 'rubygems/package_task'
  require 'rake/extensiontask'
  require 'rake/clean'
  require 'rake/testtask'
  require 'rbconfig'
  require "rdoc/task"

# rescue LoadError
end

include RbConfig
CLEAN.include 'coverage', 'doc'

############################################################
# Some Rakefile debugging and checking
############################################################


puts "**********"

if( defined?(Gem)) then
    puts "Gem is defined"
end

if defined?(Gem::PackageTask) then
    puts "PackageTask is defined"
end

if defined?(Rake::ExtensionTask) then
    puts "ExtensionTask is defined"
end

puts "**********"



NAME    = 'amatchpp'

PKG_NAME    = 'amatchpp'
PKG_VERSION = File.read('VERSION').chomp
PKG_FILES   = FileList["**/*"].exclude(/^(pkg|coverage|doc|tmp)/)

PKG_DOC_FILES = []
PKG_DOC_FILES.concat(Dir['lib/**/*.rb'])
PKG_DOC_FILES << 'README'

MAKE        = ENV['MAKE'] || %w[gmake make].find { |c| system(c, '-v') }


############################################################
# Compilation
############################################################


# rule to build the extension: this says
# that the extension should be rebuilt
# after any change to the files in ext

file "lib/#{NAME}/#{NAME}.so" =>
  Dir.glob("ext/#{NAME}/*{.rb,.c,.cpp,*.h,*.hpp}") do
  Dir.chdir("ext/#{NAME}") do
    # this does essentially the same thing
    # as what RubyGems does
    ruby "extconf.rb"
    sh "make clean"
    sh "make"
  end
  cp "ext/#{NAME}/#{NAME}.so", "lib/#{NAME}"
end


desc "Compiling library"
task :compile_ext => "lib/#{NAME}/#{NAME}.so" do
end

############################################################
# Unit testing
############################################################

desc "Run unit tests"
task :test => :compile_ext do
  #sh %{testrb -Iext:lib tests/test_*.rb}

  Rake::TestTask.new do |t|
    t.pattern = "tests/me_first.rb"
  end

  Rake::TestTask.new do |t|
    t.libs << 'lib/amatchpp' << 'tests'
    t.pattern = "tests/test_*.rb"
  end
end



############################################################
# Installation
############################################################

desc "Installing library"
task :install => :test do
  src, = Dir['ext/amatchpp.*'].reject { |x| /\.[co]$/.match x }
  filename = File.basename(src)
  dst = File.join(CONFIG["sitelibdir"], filename)
  install(src, dst, :verbose => true)
end



############################################################
# Clean
############################################################

desc "Removing generated files"
task :clean do
  cd 'ext/amatchpp' do
    ruby 'extconf.rb'
    sh "#{MAKE} distclean" if File.exist?('Makefile')
  end

  cd 'lib/amatchpp' do
    sh "rm -f *.so"
  end
end

############################################################
# Documentation
############################################################

RDoc::Task.new(:doc) do |rd|
  sh "rice_protodoc ext/amatchpp/*.cpp ext/amatchpp/*.hpp  > protodoc.rb"

  rd.main = "README"
  rd.title = "#{PKG_NAME} - Enhanced Approximate Matching"
  rd.rdoc_files.include("README", "prior_work.rdoc", "lib/**/*.rb", "protodoc.rb")
  rd.rdoc_dir = "doc"
end



##########################################################
# Packaging
############################################################



if defined?(Gem) and defined?(Gem::PackageTask) and
  defined?(Rake::ExtensionTask)
then
  spec_src = <<-GEM
    Gem::Specification.new do |s|
      s.name = '#{PKG_NAME}'
      s.version = '#{PKG_VERSION}'
      s.summary = "Approximate String Matching library"
      s.description = <<EOF
Amatch is a library for approximate string matching and searching in strings.
Several algorithms can be used to do this, and it's also possible to compute a
similarity metric number between 0.0 and 1.0 for two given strings.
EOF

      s.files = #{PKG_FILES.sort.inspect}

      s.extensions << "ext/amatchpp/extconf.rb"

      s.require_paths << 'ext' << 'lib'

      s.bindir = "bin"
      # s.executables = ["agrep.rb"]
      # s.default_executable = "agrep.rb"

      s.has_rdoc = true
      s.extra_rdoc_files.concat #{PKG_DOC_FILES.sort.inspect}
      s.rdoc_options << '--main' << 'README' <<
        '--title' << "#{PKG_NAME} - Approximate Matching"
      s.test_files.concat Dir['tests/test_*.rb']

      s.author = "Larry Dennison"
      s.email = "larry@alum.mit.edu"
      s.homepage = "http://amatch.rubyforge.org"
      s.rubyforge_project = '#{PKG_NAME}'
    end
  GEM

  desc 'Create a gemspec file'
  task :gemspec do
    File.open("#{PKG_NAME}.gemspec", 'w') do |f|
      f.puts spec_src
    end
  end

  spec = eval(spec_src)
  Gem::PackageTask.new(spec) do |pkg|
    pkg.need_tar      = true
    pkg.package_files = PKG_FILES
  end

  Rake::ExtensionTask.new do |ext|
    ext.name            = PKG_NAME
    ext.gem_spec        = spec
    ext.cross_compile   = true
    ext.cross_platform  = 'i386-mswin32'
    ext.ext_dir         = 'ext'
    ext.lib_dir         = 'lib'
  end
end

desc m = "Writing version information for #{PKG_VERSION}"
task :version do
  puts m
  File.open(File.join('lib', 'amatchpp', 'version.rb'), 'w') do |v|
    v.puts <<EOT
module Amatchpp
  # Amatchpp version
  VERSION         = '#{PKG_VERSION}'
  VERSION_ARRAY   = VERSION.split(/\\./).map { |x| x.to_i } # :nodoc:
  VERSION_MAJOR   = VERSION_ARRAY[0] # :nodoc:
  VERSION_MINOR   = VERSION_ARRAY[1] # :nodoc:
  VERSION_BUILD   = VERSION_ARRAY[2] # :nodoc:
end
EOT
  end
end


desc "Default task"
task :default => [ :version, :gemspec, :test ]

desc "Build all gems and archives for a new release."
task :release => [ :clean, :version, :gemspec, :cross, :native, :gem ] do
  system "#$0 clean native gem"
  system "#$0 clean package"
end
