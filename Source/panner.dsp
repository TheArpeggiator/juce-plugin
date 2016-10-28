import("stdfaust.lib");
attack = hslider("attack", 0.3, 0, 2, 0.1) : si.smoo;
decay = hslider("decay", 0.3, 0, 2,0.1) : si.smoo;
sustain = hslider("sustain", 0, 0, 100,2) : si.smoo;
release = hslider("release", 0.3, 0, 2,0.1) : si.smoo;

freq = hslider("frequency",440, 100, 2000,5);
gain = hslider("gain",0.9, 0, 1,0.05) : si.smoo;

pan = hslider("pan",0.5,0,1,0.01) : si.smoo;

trigger = button("gate");
synth = os.osc(freq)*gain*trigger;

env = en.adsr(attack, decay, sustain, release, trigger);

process = vgroup("syn",synth*env <: *(1-pan),*(pan) : dm.zita_rev1);