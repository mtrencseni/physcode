
type Time = Float
type Position = Float
type Velocity = Float
type Energy = Float
type Force = Float
type Mass = Float
type SpringConstant = Float
type Momentum = Float
type PositionPath      = Time -> Position
type ConfigurationPath = Time -> Position -> Velocity

-- pp2cp :: PositionPath -> ConfigurationPath

-- https://en.wikipedia.org/wiki/Harmonic_oscillator
springForce :: SpringConstant -> Position -> Force
springForce k x | k > 0 = - k * x

springEnergy :: SpringConstant -> Position -> Energy
springEnergy k x = -1 * integrate (springForce k) 0 x

-- integrate takes a function f(x) (Float -> Float)
-- two integration bounds, and returns the integral
integrate :: (Float -> Float) -> Float -> Float -> Float
integrate :: f min max = snd . integrateQNGSource f min max

-- http://www.lecture-notes.co.uk/susskind/classical-mechanics/lecture-5/harmonic-oscillator/
springLagrangian :: Mass -> Configuration -> Energy
springLagrangian m (x, v) = 0.5 * m * v * v - 0.5 * k * x * x

springHamiltonian :: Mass -> Configuration -> Energy
springHamiltonian m (x, v) = conjugateMomentum * v - springLagrangian m (x, v)

--conjugateMomentum = del_v L
conjugateMomentum :: (Mass -> Configuration -> Energy) -> (Mass -> Configuration -> Momentum)
conjugateMomentum L = D . L (v, x) v






