import qualified Numeric.Units.Dimensional.Prelude as D
import Numeric.Units.Dimensional.Prelude (
  (+), (-), (*), (/), (*~), (/~), kilo, gram, meter, second
  )
import Prelude (
  Double, ($), print, (>)
  )
import Numeric.NumType (
  Zero, Pos1, Neg2
  )

-- I.   Kinematics
-- I.a  Coordinates and related
type Time = D.Time Double
type Position = D.Length Double
type Velocity = D.Velocity Double
-- I.b  Configuration and state
type Configuration  = (Position, Velocity)
type State          = (Time, Position, Velocity)
type PositionF      = Time -> Position
type VelocityF      = Time -> Velocity
type ConfigurationF = Time -> Configuration
-- II.  Dynamics
type Energy = D.Energy Double
type Force = D.Force Double
type Mass = D.Mass Double
type EnergyF        = Parameters -> Configuration -> Energy
type ForceF         = Parameters -> Configuration -> Position -> Force
-- III. Constants
type SpringConstant = (D.Quantity (D.Dim Zero Pos1 Neg2 Zero Zero Zero Zero)) Double -- kg/s^2
type Parameters     = (Mass, SpringConstant)


-- position x(t) to velocity v(t)
pf2vf :: PositionF -> Time -> VelocityF
pf2vf x dt = (\t -> v(t))
    where v(t) = (x(t + dt) - x(t)) / dt

-- position x(t) to configuration (x(t), v(t))
pf2cf :: PositionF -> Time -> ConfigurationF
pf2cf x dt = (\t -> (x t, pf2vf x dt $ t))

-- lagrangian L(m, k, x(t), v(t)) to force F(m, k, dx, x(t), v(t))
lf2ff :: EnergyF -> ForceF
lf2ff l = \(m, k) -> \(x, v) -> \dx -> (l (m, k) (x + dx, v) - l (m, k) (x, v)) / dx
-- in case of the harmonic oscillator, this derivative works out to -k*x

-- lagrangian L(m, k, x(t), v(t)) to potential energy
lf2pf :: EnergyF -> EnergyF
lf2pf l = \(m, k) -> \(x, v) -> m * v * v / D._2 - l (m, k) (x, v)

-- the harmonic oscillator lagrangian L(m, k, x, v) = 1/2 * m * v^2 - 1/2 * k * x^2
lagrangian :: EnergyF
lagrangian (m, k) (x, v)
  | k /~ ((kilo gram) / (second * second)) > 0 -- k > 0
  = m * v * v / D._2 - k * x * x / D._2

main = do
    print $ f
    where
        f = (lf2ff lagrangian) (m, k) (x, v) dx
        m =  1     *~ (kilo gram)
        k =  3     *~ ((kilo gram) / (second * second))
        x =  5     *~ (meter)
        v =  9     *~ (meter / second)
        dx = 0.001 *~ (meter)
