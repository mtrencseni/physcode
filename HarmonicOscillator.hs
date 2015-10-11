
-- todo: dimensions?
-- https://github.com/bjornbm/dimensional-tf
-- todo: k>0
-- kinematics
type Time = Double
type TimeInterval = Double
type Position = Double
type PositionInterval = Double
type Velocity = Double
type VelocityInterval = Double
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
type Parameters     = (Mass, SpringConstant)
type EnergyF        = Parameters -> Configuration -> Energy
type ForceF         = Parameters -> Configuration -> PositionInterval -> Force

-- position to velocity
pf2vf :: PositionF -> TimeInterval -> VelocityF
pf2vf x dt = (\t -> v(t))
    where v(t) = (x(t + dt) - x(t)) / dt

-- position to configuration
pf2cf :: PositionF -> TimeInterval -> ConfigurationF
pf2cf x dt = (\t -> (x t, pf2vf x dt $ t))

-- lagrangian to force
lf2ff :: EnergyF -> ForceF
lf2ff l = \(m, k) -> \(x, v) -> \dx -> (l (m, k) (x + dx, v) - l (m, k) (x, v)) / dx
-- in case of the harmonic oscillator, this derivative works out to -k*x

-- lagrangian to potential energy
lf2pf :: EnergyF -> EnergyF
lf2pf l = \(m, k) -> \(x, v) -> 0.5 * m * v * v - l (m, k) (x, v)

-- springHamiltonian :: Mass -> Configuration -> Energy
-- springHamiltonian m (x, v) = conjugateMomentum * v - springLagrangian m (x, v)

--conjugateMomentum = del_v L
-- conjugateMomentum :: (Mass -> Configuration -> Energy) -> (Mass -> Configuration -> Momentum)
-- conjugateMomentum L = D . L (v, x) v

-- http://www.lecture-notes.co.uk/susskind/classical-mechanics/lecture-5/harmonic-oscillator/
-- this is the only function I'm specifying explicitly
-- this is the theory
lagrangian :: EnergyF
lagrangian (m, k) (x, v) = 0.5 * m * v * v - 0.5 * k * x * x

main = do
    print $ f
    where
        f = (lf2ff lagrangian) (m, k) (x, v) dx
        m = 1
        k = 3
        x = 5
        v = 9
        dx = 0.001
    -- print $ config 5
    -- where
    --     x  = (\t -> t * t)
    --     dt = 0.001
    --     config = pf2cf x dt
