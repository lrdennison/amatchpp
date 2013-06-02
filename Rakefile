# vim: set filetype=ruby et sw=2 ts=2:

begin
  # require 'rake/gempackagetask'
  require 'rubygems/package_task'
  require 'rake/extensiontask'
# rescue LoadError
end

require 'rbconfig'
include RbConfig

require 'rake/clean'
CLEAN.include 'coverage', 'doc'
require 'rake/testtask'

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

MAKE        = ENV['MAKE'] || %w[gmake make].find { |c| system(c, '-v') }
PKG_NAME    = 'amatchpp'
PKG_VERSION = File.read('VERSION').chomp
PKG_FILES   = FileList["**/*"].exclude(/^(pkg|coverage|doc|tmp)/)
PKG_DOC_FILES = [ "ext/amatch.c" ].concat(Dir['lib/**/*.rb']) << 'README'

desc "Run unit tests"
task :test => :compile_ext do
  #sh %{testrb -Iext:lib tests/test_*.rb}

  Rake::TestTask.new do |t|
    t.pattern = "tests/me_first.rb"
  end

  Rake::TestTask.new do |t|
    t.libs=["ext"]
    t.pattern = "tests/test_*.rb"
  end
end

desc "Compiling library"
task :compile_ext do
  cd 'ext'  do
    ruby %{extconf.rb}
    sh MAKE
  end
end

desc "Installing library"
task :install => :test do
  src, = Dir['ext/amatchpp.*'].reject { |x| /\.[co]$/.match x }
  filename = File.basename(src)
  dst = File.join(CONFIG["sitelibdir"], filename)
  install(src, dst, :verbose => true)
end

desc "Removing generated files"
task :clean do
  cd 'ext' do
    ruby 'extconf.rb'
    sh "#{MAKE} distclean" if File.exist?('Makefile')
  end
end

desc "Build the documentation"
task :doc do
  sh "rdoc -m README -t '#{PKG_NAME} - Approximate Matching' #{PKG_DOC_FILES * ' '}"
end


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

      s.extensions << "ext/extconf.rb"

      s.require_paths << 'ext' << 'lib'

      s.bindir = "bin"
      s.executables = ["agrep.rb"]
      s.default_executable = "agrep.rb"

      s.has_rdoc = true
      s.extra_rdoc_files.concat #{PKG_DOC_FILES.sort.inspect}
      s.rdoc_options << '--main' << 'README' <<
        '--title' << "#{PKG_NAME} - Approximate Matching"
      s.test_files.concat Dir['tests/test_*.rb']

      s.author = "Florian Frank"
      s.email = "flori@ping.de"
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
  # Amatch version
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
