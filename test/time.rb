assert 'SFML::Time' do
  a = SFML.seconds(1)
  aa = SFML.seconds(1)
  b = SFML.seconds(2)
  bb = SFML.seconds(2)
  c = a + b
  d = c - a
  e = d * 2
  f = e / 2

  assert_true a < b
  assert_true b > a
  assert_true b != a
  assert_equal aa, a
  assert_equal bb, b
  assert_equal SFML.seconds(3), c
  assert_equal SFML.seconds(2), d
  assert_equal SFML.seconds(4), e
  assert_equal SFML.seconds(2), f
end
