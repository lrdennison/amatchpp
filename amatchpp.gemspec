    Gem::Specification.new do |s|
      s.name = 'amatchpp'
      s.version = '0.0.1'
      s.summary = "Approximate String Matching library"
      s.description = <<EOF
Amatch is a library for approximate string matching and searching in strings.
Several algorithms can be used to do this, and it's also possible to compute a
similarity metric number between 0.0 and 1.0 for two given strings.
EOF

      s.files = ["Gemfile", "Gemfile.lock", "Makefile", "README.md", "Rakefile", "VERSION", "amatchpp.gemspec", "ext", "ext/amatchpp", "ext/amatchpp/DynProg.cpp", "ext/amatchpp/DynProg.hpp", "ext/amatchpp/DynProg.o", "ext/amatchpp/General.cpp", "ext/amatchpp/General.hpp", "ext/amatchpp/General.o", "ext/amatchpp/Hamming.cpp", "ext/amatchpp/Hamming.hpp", "ext/amatchpp/Hamming.o", "ext/amatchpp/Levenshtein.cpp", "ext/amatchpp/Levenshtein.hpp", "ext/amatchpp/Levenshtein.o", "ext/amatchpp/LongestSubsequence.cpp", "ext/amatchpp/LongestSubsequence.hpp", "ext/amatchpp/LongestSubsequence.o", "ext/amatchpp/LongestSubstring.cpp", "ext/amatchpp/LongestSubstring.hpp", "ext/amatchpp/LongestSubstring.o", "ext/amatchpp/Makefile", "ext/amatchpp/Sellers.cpp", "ext/amatchpp/Sellers.hpp", "ext/amatchpp/Sellers.o", "ext/amatchpp/amatch.orig", "ext/amatchpp/amatchpp.cpp", "ext/amatchpp/amatchpp.o", "ext/amatchpp/amatchpp.so", "ext/amatchpp/extconf.rb", "ext/amatchpp/utils.hpp", "lib", "lib/amatchpp", "lib/amatchpp/amatchpp.so", "lib/amatchpp/version.rb", "tests", "tests/me_first.rb", "tests/test_amatchpp.rb", "tests/test_hamming.rb", "tests/test_levenshtein.rb", "tests/test_longest_subsequence.rb", "tests/test_longest_substring.rb", "tests/test_sellers.rb"]

      s.extensions << "ext/extconf.rb"

      s.require_paths << 'ext' << 'lib'

      s.bindir = "bin"
      s.executables = ["agrep.rb"]
      s.default_executable = "agrep.rb"

      s.has_rdoc = true
      s.extra_rdoc_files.concat ["README", "ext/amatch.c", "lib/amatchpp/version.rb"]
      s.rdoc_options << '--main' << 'README' <<
        '--title' << "amatchpp - Approximate Matching"
      s.test_files.concat Dir['tests/test_*.rb']

      s.author = "Florian Frank"
      s.email = "flori@ping.de"
      s.homepage = "http://amatch.rubyforge.org"
      s.rubyforge_project = 'amatchpp'
    end
