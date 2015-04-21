module SFML
  class Time
    include Comparable

    def initialize
    end

    # @return [Integer]
    def as_seconds
    end

    # @return [Integer]
    def as_milliseconds
    end

    # @return [Integer]
    def as_microseconds
    end

    # @param [SFML::Time] other
    # @return [Boolean]
    def <=>(other)
    end

    # @param [SFML::Time] other
    # @return [SFML::Time]
    def +(other)
    end

    # @param [SFML::Time] other
    # @return [SFML::Time]
    def -(other)
    end

    # @param [SFML::Time] other
    # @return [SFML::Time]
    def *(other)
    end

    # @param [SFML::Time] other
    # @return [SFML::Time]
    def /(other)
    end
  end
end
