module SFML
  # Vector3 is an abstract class for all the other Vector3 variants
  # This is only a docstub, the actual Class doesn't define any of these
  # methods, each subclass has its own specialized set.
  class Vector3
    # @!attribute x
    #   @return [Numeric]
    attr_accessor :x
    # @!attribute y
    #   @return [Numeric]
    attr_accessor :y
    # @!attribute z
    #   @return [Numeric]
    attr_accessor :z

    # @param [Numeric] x
    # @param [Numeric] y
    # @param [Numeric] z
    def initialize(x = 0, y = 0, z = 0)
    end
  end
end
