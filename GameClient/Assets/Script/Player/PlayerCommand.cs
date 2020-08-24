using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCommand
{
    public virtual void Execute(PlayerActor actor) { }
    public virtual void Execute(PlayerActor actor,float _speed) { }
    public virtual void Execute(PlayerActor actor, PlayerState PT) { }
}

public class CalcDir : PlayerCommand
{
    public override void Execute(PlayerActor actor, PlayerState PT)
    {
        actor.CalcDir(PT);
    }
}

public class ResetDir : PlayerCommand
{
    public override void Execute(PlayerActor actor, PlayerState PT)
    {
        actor.ResetDir(PT);
    }
}

public class Move : PlayerCommand
{
    public override void Execute(PlayerActor actor, float _speed)
    {
        //actor.SimulatonMove(_speed);
    }
}

public class Attack:PlayerCommand
{
    public override void Execute(PlayerActor actor,PlayerState PT)
    {
        actor.SendAttack(PT);
    }
}