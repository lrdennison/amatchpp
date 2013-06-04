require 'minitest/autorun'
require 'amatchpp'
require 'amatch'

class TestSellers < Minitest::Test

  def setup
    @empty = Amatchpp::Sellers.new()
    @reference = Amatch::Sellers.new('pattern')
  end

  def test_pattern
    @empty.pattern = "pattern";
    assert_equal "pattern", @empty.pattern
  end

  def test_reference
    result = @reference.search( "aaapatternbbbb");
    assert_equal result, 0.0, "Should be an exact match"
  end

  def test_search
    @empty.pattern = "pattern";
    result = @empty.search( "aaapatternbbbb");
    assert_equal result, 0.0, "Should be an exact match"
    result = @empty.search( ["thing1", "thing2", "thing3"] );
    puts result
  end


end
