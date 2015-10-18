import qualified Numeric.Units.Dimensional.Prelude as D
import Numeric.Units.Dimensional.Prelude (
  (+), (-), (*), (/), (*~), (/~), kilo, gram, meter, second
  )
import Prelude (
  Integer, Double, ($), print, (>), (==), Maybe(..), pred
  )
import Numeric.NumType (
  Zero, Pos1, Neg1, Neg2
  )
import Data.List (unfoldr)

-- I.   Kinematics
-- I.a  Coordinates and related
type Time           = D.Time Double
type Position       = D.Length Double
type Velocity       = D.Velocity Double
type Acceleration   = D.Acceleration Double
-- I.b  Configuration and state
type Configuration  = (Position, Velocity)
type State          = (Time, Position, Velocity)
type PositionF      = Time -> Position
type VelocityF      = Time -> Velocity
type ConfigurationF = Time -> Configuration
-- II.  Dynamics
type Energy          = D.Energy Double
type Force           = D.Force Double
type Mass            = D.Mass Double
type EnergyF         = Parameters -> Configuration -> Energy
type ForceF          = Parameters -> Configuration -> Force
type AccelerationF   = Parameters -> Configuration -> Acceleration
-- III. Constants
type SpringConstant  = (D.Quantity (D.Dim Zero Pos1 Neg2 Zero Zero Zero Zero)) Double -- kg/s^2
type DampingConstant = (D.Quantity (D.Dim Zero Pos1 Neg1 Zero Zero Zero Zero)) Double -- kg/s
type Parameters      = (Mass, SpringConstant, DampingConstant)

-- position x(t) to velocity v(t)
pf2vf :: PositionF -> Time -> VelocityF
pf2vf x dt = (\t -> v(t))
    where v(t) = (x(t + dt) - x(t)) / dt

-- position x(t) to configuration (x(t), v(t))
pf2cf :: PositionF -> Time -> ConfigurationF
pf2cf x dt = (\t -> (x t, pf2vf x dt $ t))

-- force F(m, k, x, v) to acceleration a(m, k, x, v)
ff2af :: ForceF -> AccelerationF
ff2af f = \(m, k, c) -> \(x, v) -> (f (m, k, c) (x, v)) / m

-- solve the system at steps dt for n steps
solve :: AccelerationF -> Parameters -> Configuration -> Time -> Integer -> [Configuration]
solve a params config0 dt n = unfoldr f (config0, n)
  where f (config, i) = if i == 0 then Nothing
                        else           Just(config, (step a params config dt, pred i))

step :: AccelerationF -> Parameters -> Configuration -> Time -> Configuration
step a (m, k, c) (x, v) dt = (x + dx, v + dv)
  where dx = v * dt
        dv = a (m, k, c) (x, v) * dt

-- the damped oscillator force f(k, c, x, v) = - k*x - c*v
force :: ForceF
force (_, k, c) (x, v) = ((-1) *~ D.one) * k * x - c * v

main = do
    print $ solve a (m, k, c) (x0, v0) dt 3
    where
        a =   ff2af force
        m =   1     *~ (kilo gram)
        k =   3     *~ ((kilo gram) / (second * second))
        c =   4     *~ ((kilo gram) / second)
        x0 =  5     *~ (meter)
        v0 =  9     *~ (meter / second)
        dt =  0.001 *~ (second)
