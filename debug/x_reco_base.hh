#include <cmath>

struct Environment
{
    double L_N, L_F;
    double v_N, v_F;

    void Init()
    {
        v_N = -2.22676133379662;
        v_F = -1.90985828033614;

        L_N = 36.5451226794256E3;   // mm
        L_F = 28.2017100011691E3;   // mm
    }
};

struct Kinematics
{
    double th, vtx;
};

struct Event
{
    double x_N, x_F;
};

Event Propagate(const Kinematics &k, const Environment &env)
{
    Event e;
    e.x_N = env.L_N * k.th + env.v_N * k.vtx;
    e.x_F = env.L_F * k.th + env.v_F * k.vtx;

    return e;
}

Kinematics Reconstruct(const Event &ev, const Environment &env)
{
    const double D = env.v_F * env.L_N - env.v_N * env.L_F;

    Kinematics k;
    k.th = (env.v_F * ev.x_N - env.v_N * ev.x_F) / D;
    k.vtx = (ev.x_F * env.L_N - ev.x_N * env.L_F) / D;

    return k;
}

//----------------------------------------------------------------------------------------------------

Environment GetBiasedEnvironment(const Environment &env, double al, double be)
{
    Environment env_p;

    {
        const double C = cos(al), S = sin(al);
        env_p.L_N = +C * env.L_N + S * env.L_F;
        env_p.L_F = -S * env.L_N + C * env.L_F;
    }

    {
        const double C = cos(be), S = sin(be);
        env_p.v_N = +C * env.v_N + S * env.v_F;
        env_p.v_F = -S * env.v_N + C * env.v_F;
    }

    return env_p;
}