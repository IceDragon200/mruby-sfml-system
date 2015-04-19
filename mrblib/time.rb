module SFML
  class Time
    # @return [String]
    def inspect
      "<#{self.class} seconds=#{as_seconds}>"
    end
  end
end
