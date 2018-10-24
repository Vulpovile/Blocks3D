#ifndef ENUM_H
#define ENUM_H
static enum BinType {GameTool, Grab, Clone, Hammer};
static enum ControllerType {None, KeyboardRight, KeyboardLeft, Joypad1, Joypad2, Chase, Flee};
//static enum JointType {UNK0, WeldJoint, SnapJoint, UNK3, Rotate, RotateP, RotateV, GlueJoint, UNK8, UNK9, None};
static enum ActionType {Nothing, Pause, Lose, Draw, Win};
static enum AffectType {NoChange, Increase, Decrease};
static enum InputType {NoInput, LeftTread, RightTread, Steer, Throtle, UpDown, Action1, Action2, Action3, Action4, Action5, Constant, Sin};
//static enum SurfaceConstraint {None, Hinge, SteppingMotor, Motor};
static enum SurfaceType{Smooth, Snaps, Inlets, Glue, Weld, Hinge, Motor, Bumps};
static enum SoundType {NoSound, Boing, Bomb, Break, Click, Clock, Slingshot, Page, Ping, Snap, Splat, Step, StepOn, Swoosh, Victory};
static enum PartType {Ball, Block, Cylinder};
static enum KeywordFilterType {Include, Exclude};
#endif
