assert 'SFML::Clock' do
  clock = SFML::Clock.new
  assert_kind_of SFML::Time, clock.elapsed_time
  assert_kind_of SFML::Time, clock.restart
end
