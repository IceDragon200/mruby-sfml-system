module SFML
  # Vector2 is an abstract class for all the other Vector2 variants.
  # This is only a docstub, the actual Class doesn't define any of these
  # methods, each subclass has its own specialized set.
  class Vector2
    # @!attribute x
    #   @return [Numeric]
    attr_accessor :x
    # @!attribute y
    #   @return [Numeric]
    attr_accessor :y

    # @param [Numeric] x
    # @param [Numeric] y
    def initialize(x = 0, y = 0)
    end
  end
end
