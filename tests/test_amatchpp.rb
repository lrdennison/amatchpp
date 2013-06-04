require 'minitest/autorun'
require 'amatchpp'


class TestAmatchpp < Minitest::Test

  def setup
  end

  def test_module
    assert defined?( Amatchpp), "module 'Amatchpp' isn't defined"

    assert defined?( Amatchpp::General), "class 'Amatchpp' isn't defined"
    assert defined?( Amatchpp::DynProg), "class 'DynProg' isn't defined"
    assert defined?( Amatchpp::Sellers), "class 'Sellers' isn't defined"
    assert defined?( Amatchpp::Levenshtein), "class 'Levenshtein' isn't defined"
  end

end
