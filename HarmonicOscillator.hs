
import qualified Numeric.Units.Dimensional.Prelude as D
import Numeric.Units.Dimensional.Prelude((+), (-), (*), (/), (*~), kilo, gram, meter, second)
import Prelude (Double, ($), print)
import Numeric.NumType (Zero, Pos1, Neg2)

-- todo: k>0
-- kinematics
type Time = D.Time Double
type Position = D.Length Double
type Velocity = D.Velocity Double
--type Momentum = Double
type Configuration  = (Position, Velocity)
type State          = (Time, Position, Velocity)
type PositionF      = Time -> Position
type VelocityF      = Time -> Velocity
type ConfigurationF = Time -> Configuration
-- dynamics
type Energy = D.Energy Double
type Force = D.Force Double
type Mass = D.Mass Double
type SpringConstant = (D.Quantity (D.Dim Zero Pos1 Neg2 Zero Zero Zero Zero)) Double -- kg/s^2
type Parameters     = (Mass, SpringConstant)
type EnergyF        = Parameters -> Configuration -> Energy
type ForceF         = Parameters -> Configuration -> Position -> Force

-- position to velocity
pf2vf :: PositionF -> Time -> VelocityF
pf2vf x dt = (\t -> v(t))
    where v(t) = (x(t + dt) - x(t)) / dt

-- position to configuration
pf2cf :: PositionF -> Time -> ConfigurationF
pf2cf x dt = (\t -> (x t, pf2vf x dt $ t))

-- lagrangian to force
lf2ff :: EnergyF -> ForceF
lf2ff l = \(m, k) -> \(x, v) -> \dx -> (l (m, k) (x + dx, v) - l (m, k) (x, v)) / dx
-- in case of the harmonic oscillator, this derivative works out to -k*x

-- lagrangian to potential energy
lf2pf :: EnergyF -> EnergyF
lf2pf l = \(m, k) -> \(x, v) -> m * v * v / D._2 - l (m, k) (x, v)

-- springHamiltonian :: Mass -> Configuration -> Energy
-- springHamiltonian m (x, v) = conjugateMomentum * v - springLagrangian m (x, v)

--conjugateMomentum = del_v L
-- conjugateMomentum :: (Mass -> Configuration -> Energy) -> (Mass -> Configuration -> Momentum)
-- conjugateMomentum L = D . L (v, x) v

-- http://www.lecture-notes.co.uk/susskind/classical-mechanics/lecture-5/harmonic-oscillator/
-- this is the only function I'm specifying explicitly
-- this is the theory
lagrangian :: EnergyF
lagrangian (m, k) (x, v) = m * v * v / D._2 - k * x * x / D._2

main = do
    print $ f
    where
        f = (lf2ff lagrangian) (m, k) (x, v) dx
        m =  1     *~ (kilo gram)
        k =  3     *~ ((kilo gram) / (second * second))
        x =  5     *~ (meter)
        v =  9     *~ (meter / second)
        dx = 0.001 *~ (meter)
    -- print $ config 5
    -- where
    --     x  = (\t -> t * t)
    --     dt = 0.001
    --     config = pf2cf x dt
