
-- todo: dimensions?
-- kinematics
type Time = Double
type TimeInterval = Double
type Position = Double
type Velocity = Double
type Momentum = Double
type Configuration  = (Position, Velocity)
type State          = (Time, Position, Velocity)
type PositionF      = Time -> Position
type VelocityF      = Time -> Velocity
type ConfigurationF = Time -> Configuration
-- dynamics
type Energy = Double
type Force = Double
type Mass = Double
type SpringConstant = Double
type LagrangianF    = Mass -> SpringConstant -> Configuration -> Energy
type ForceF         = SpringConstant -> Time -> Force

pf2vf :: PositionF -> TimeInterval -> VelocityF
pf2vf x dt = (\t -> v(t))
    where v(t) = (x(t + dt) - x(t)) / dt

pf2cf :: PositionF -> TimeInterval -> ConfigurationF
pf2cf x dt = (\t -> (x t, pf2vf x dt $ t))

-- http://www.lecture-notes.co.uk/susskind/classical-mechanics/lecture-5/harmonic-oscillator/
lagrangian :: LagrangianF
lagrangian m k (x, v) = 0.5 * m * v * v - 0.5 * k * x * x

force :: LagrangianF -> ForceF
force l = (l(v + dv) - l(v)) / dv

main = do
    print $ config 5
    where
        x  = (\t -> t * t)
        dt = 0.00001
        config = pf2cf x dt

-- https://en.wikipedia.org/wiki/Harmonic_oscillator
-- springForce :: SpringConstant -> Position -> Force
-- springForce k x | k > 0 = - k * x

-- springEnergy :: SpringConstant -> Position -> Energy
-- springEnergy k x = -1 * integrate (springForce k) 0 x

-- integrate takes a function f(x) (Double -> Double)
-- two integration bounds, and returns the integral
-- integrate :: (Double -> Double) -> Double -> Double -> Double
-- integrate :: f min max = snd . integrateQNGSource f min max

-- springHamiltonian :: Mass -> Configuration -> Energy
-- springHamiltonian m (x, v) = conjugateMomentum * v - springLagrangian m (x, v)

--conjugateMomentum = del_v L
-- conjugateMomentum :: (Mass -> Configuration -> Energy) -> (Mass -> Configuration -> Momentum)
-- conjugateMomentum L = D . L (v, x) v
