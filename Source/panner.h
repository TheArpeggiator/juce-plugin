//----------------------------------------------------------
//
// Code generated with Faust 0.9.92 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust architecture file to easily integrate a Faust DSP module
// in a JUCE project

// needed by any Faust arch file
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


// allows to control a Faust DSP module in a simple manner by using parameter's path
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H

// needed by any Faust arch file
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

// tags used by the Faust compiler to paste the generated c++ code
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS Pan
#endif

class Pan : public dsp {
  private:
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	float 	fRec10[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec11[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec13[2];
	FAUSTFLOAT 	fbutton0;
	FAUSTFLOAT 	fslider3;
	float 	fRec14[2];
	float 	fConst0;
	FAUSTFLOAT 	fslider4;
	float 	fRec15[2];
	float 	fRec16[2];
	float 	fConst1;
	float 	fRec12[2];
	float 	fRec17[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec18[2];
	FAUSTFLOAT 	fslider6;
	float 	fConst2;
	float 	fRec19[2];
	float 	fRec20[2];
	int 	IOTA;
	float 	fVec1[8192];
	FAUSTFLOAT 	fslider7;
	float 	fConst3;
	FAUSTFLOAT 	fslider8;
	float 	fConst4;
	float 	fRec22[2];
	FAUSTFLOAT 	fslider9;
	float 	fConst5;
	float 	fConst6;
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	float 	fConst7;
	float 	fRec21[2];
	float 	fVec2[16384];
	float 	fConst8;
	int 	iConst9;
	float 	fVec3[1024];
	int 	iConst10;
	float 	fRec8[2];
	float 	fRec26[2];
	float 	fConst11;
	float 	fConst12;
	float 	fRec25[2];
	float 	fVec4[16384];
	float 	fConst13;
	int 	iConst14;
	float 	fVec5[2048];
	int 	iConst15;
	float 	fRec23[2];
	float 	fRec30[2];
	float 	fConst16;
	float 	fConst17;
	float 	fRec29[2];
	float 	fVec6[8192];
	float 	fConst18;
	int 	iConst19;
	float 	fVec7[2048];
	int 	iConst20;
	float 	fRec27[2];
	float 	fRec34[2];
	float 	fConst21;
	float 	fConst22;
	float 	fRec33[2];
	float 	fVec8[16384];
	float 	fConst23;
	int 	iConst24;
	float 	fVec9[2048];
	int 	iConst25;
	float 	fRec31[2];
	float 	fVec10[8192];
	float 	fRec38[2];
	float 	fConst26;
	float 	fConst27;
	float 	fRec37[2];
	float 	fVec11[8192];
	float 	fConst28;
	int 	iConst29;
	float 	fVec12[1024];
	int 	iConst30;
	float 	fRec35[2];
	float 	fRec42[2];
	float 	fConst31;
	float 	fConst32;
	float 	fRec41[2];
	float 	fVec13[8192];
	float 	fConst33;
	int 	iConst34;
	float 	fVec14[2048];
	int 	iConst35;
	float 	fRec39[2];
	float 	fRec46[2];
	float 	fConst36;
	float 	fConst37;
	float 	fRec45[2];
	float 	fVec15[8192];
	float 	fConst38;
	int 	iConst39;
	float 	fVec16[2048];
	int 	iConst40;
	float 	fRec43[2];
	float 	fRec50[2];
	float 	fConst41;
	float 	fConst42;
	float 	fRec49[2];
	float 	fVec17[8192];
	float 	fConst43;
	int 	iConst44;
	float 	fVec18[1024];
	int 	iConst45;
	float 	fRec47[2];
	float 	fRec0[3];
	float 	fRec1[3];
	float 	fRec2[3];
	float 	fRec3[3];
	float 	fRec4[3];
	float 	fRec5[3];
	float 	fRec6[3];
	float 	fRec7[3];
	FAUSTFLOAT 	fslider12;
	FAUSTFLOAT 	fslider13;
	float 	fRec51[3];
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	float 	fRec52[3];
	FAUSTFLOAT 	fslider16;
	float 	fRec53[2];
	FAUSTFLOAT 	fslider17;
	float 	fRec54[2];
	float 	fRec55[3];
	float 	fRec56[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("reverb.lib/name", "Faust Reverb Library");
		m->declare("reverb.lib/version", "0.0");
		m->declare("route.lib/name", "Faust Signal Routing Library");
		m->declare("route.lib/version", "0.0");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("envelope.lib/name", "Faust Envelope Library");
		m->declare("envelope.lib/version", "0.0");
		m->declare("envelope.lib/author", "GRAME");
		m->declare("envelope.lib/copyright", "GRAME");
		m->declare("envelope.lib/license", "LGPL with exception");
		m->declare("miscoscillator.lib/name", "Faust Oscillator Library");
		m->declare("miscoscillator.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (1.0f / fConst0);
		fConst2 = (6.2831855f / fConst0);
		fConst3 = (0.001f * fConst0);
		fConst4 = (3.1415927f / fConst0);
		fConst5 = floorf(((0.219991f * fConst0) + 0.5f));
		fConst6 = ((0 - (6.9077554f * fConst5)) / fConst0);
		fConst7 = (6.2831855f / float(fConst0));
		fConst8 = floorf(((0.019123f * fConst0) + 0.5f));
		iConst9 = int((int((fConst5 - fConst8)) & 16383));
		iConst10 = int((int((fConst8 + -1)) & 1023));
		fConst11 = floorf(((0.256891f * fConst0) + 0.5f));
		fConst12 = ((0 - (6.9077554f * fConst11)) / fConst0);
		fConst13 = floorf(((0.027333f * fConst0) + 0.5f));
		iConst14 = int((int((fConst11 - fConst13)) & 16383));
		iConst15 = int((int((fConst13 + -1)) & 2047));
		fConst16 = floorf(((0.192303f * fConst0) + 0.5f));
		fConst17 = ((0 - (6.9077554f * fConst16)) / fConst0);
		fConst18 = floorf(((0.029291f * fConst0) + 0.5f));
		iConst19 = int((int((fConst16 - fConst18)) & 8191));
		iConst20 = int((int((fConst18 + -1)) & 2047));
		fConst21 = floorf(((0.210389f * fConst0) + 0.5f));
		fConst22 = ((0 - (6.9077554f * fConst21)) / fConst0);
		fConst23 = floorf(((0.024421f * fConst0) + 0.5f));
		iConst24 = int((int((fConst21 - fConst23)) & 16383));
		iConst25 = int((int((fConst23 + -1)) & 2047));
		fConst26 = floorf(((0.125f * fConst0) + 0.5f));
		fConst27 = ((0 - (6.9077554f * fConst26)) / fConst0);
		fConst28 = floorf(((0.013458f * fConst0) + 0.5f));
		iConst29 = int((int((fConst26 - fConst28)) & 8191));
		iConst30 = int((int((fConst28 + -1)) & 1023));
		fConst31 = floorf(((0.127837f * fConst0) + 0.5f));
		fConst32 = ((0 - (6.9077554f * fConst31)) / fConst0);
		fConst33 = floorf(((0.031604f * fConst0) + 0.5f));
		iConst34 = int((int((fConst31 - fConst33)) & 8191));
		iConst35 = int((int((fConst33 + -1)) & 2047));
		fConst36 = floorf(((0.174713f * fConst0) + 0.5f));
		fConst37 = ((0 - (6.9077554f * fConst36)) / fConst0);
		fConst38 = floorf(((0.022904f * fConst0) + 0.5f));
		iConst39 = int((int((fConst36 - fConst38)) & 8191));
		iConst40 = int((int((fConst38 + -1)) & 2047));
		fConst41 = floorf(((0.153129f * fConst0) + 0.5f));
		fConst42 = ((0 - (6.9077554f * fConst41)) / fConst0);
		fConst43 = floorf(((0.020346f * fConst0) + 0.5f));
		iConst44 = int((int((fConst41 - fConst43)) & 8191));
		iConst45 = int((int((fConst43 + -1)) & 1023));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.3f;
		fslider2 = 0.0f;
		fbutton0 = 0.0;
		fslider3 = 0.3f;
		fslider4 = 0.3f;
		fslider5 = 0.9f;
		fslider6 = 4.4e+02f;
		fslider7 = 6e+01f;
		fslider8 = 2e+02f;
		fslider9 = 2.0f;
		fslider10 = 3.0f;
		fslider11 = 6e+03f;
		fslider12 = 0.0f;
		fslider13 = 315.0f;
		fslider14 = 0.0f;
		fslider15 = 1.5e+03f;
		fslider16 = 0.0f;
		fslider17 = 0.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<16384; i++) fVec2[i] = 0;
		for (int i=0; i<1024; i++) fVec3[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec26[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<16384; i++) fVec4[i] = 0;
		for (int i=0; i<2048; i++) fVec5[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<8192; i++) fVec6[i] = 0;
		for (int i=0; i<2048; i++) fVec7[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<16384; i++) fVec8[i] = 0;
		for (int i=0; i<2048; i++) fVec9[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<8192; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec38[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<8192; i++) fVec11[i] = 0;
		for (int i=0; i<1024; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec41[i] = 0;
		for (int i=0; i<8192; i++) fVec13[i] = 0;
		for (int i=0; i<2048; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<2; i++) fRec46[i] = 0;
		for (int i=0; i<2; i++) fRec45[i] = 0;
		for (int i=0; i<8192; i++) fVec15[i] = 0;
		for (int i=0; i<2048; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<2; i++) fRec50[i] = 0;
		for (int i=0; i<2; i++) fRec49[i] = 0;
		for (int i=0; i<8192; i++) fVec17[i] = 0;
		for (int i=0; i<1024; i++) fVec18[i] = 0;
		for (int i=0; i<2; i++) fRec47[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec51[i] = 0;
		for (int i=0; i<3; i++) fRec52[i] = 0;
		for (int i=0; i<2; i++) fRec53[i] = 0;
		for (int i=0; i<2; i++) fRec54[i] = 0;
		for (int i=0; i<3; i++) fRec55[i] = 0;
		for (int i=0; i<3; i++) fRec56[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual Pan* clone() {
		return new Pan();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("syn");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER       ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverb.lib for documentation and       references");
		ui_interface->openHorizontalBox("Zita_Rev1");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Input");
		ui_interface->declare(&fslider7, "1", "");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->declare(&fslider7, "tooltip", "Delay in ms    before reverberation begins");
		ui_interface->declare(&fslider7, "unit", "ms");
		ui_interface->addVerticalSlider("In Delay", &fslider7, 6e+01f, 2e+01f, 1e+02f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface->declare(&fslider8, "1", "");
		ui_interface->declare(&fslider8, "scale", "log");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->declare(&fslider8, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fslider8, 2e+02f, 5e+01f, 1e+03f, 1.0f);
		ui_interface->declare(&fslider10, "2", "");
		ui_interface->declare(&fslider10, "scale", "log");
		ui_interface->declare(&fslider10, "style", "knob");
		ui_interface->declare(&fslider10, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fslider10, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fslider10, 3.0f, 1.0f, 8.0f, 0.1f);
		ui_interface->declare(&fslider9, "3", "");
		ui_interface->declare(&fslider9, "scale", "log");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->declare(&fslider9, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fslider9, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fslider9, 2.0f, 1.0f, 8.0f, 0.1f);
		ui_interface->declare(&fslider11, "4", "");
		ui_interface->declare(&fslider11, "scale", "log");
		ui_interface->declare(&fslider11, "style", "knob");
		ui_interface->declare(&fslider11, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fslider11, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fslider11, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface->declare(&fslider13, "1", "");
		ui_interface->declare(&fslider13, "scale", "log");
		ui_interface->declare(&fslider13, "style", "knob");
		ui_interface->declare(&fslider13, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fslider13, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq1 Freq", &fslider13, 315.0f, 4e+01f, 2.5e+03f, 1.0f);
		ui_interface->declare(&fslider12, "2", "");
		ui_interface->declare(&fslider12, "style", "knob");
		ui_interface->declare(&fslider12, "tooltip", "Peak level    in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fslider12, "unit", "dB");
		ui_interface->addVerticalSlider("Eq1 Level", &fslider12, 0.0f, -15.0f, 15.0f, 0.1f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface->declare(&fslider15, "1", "");
		ui_interface->declare(&fslider15, "scale", "log");
		ui_interface->declare(&fslider15, "style", "knob");
		ui_interface->declare(&fslider15, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fslider15, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq2 Freq", &fslider15, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f);
		ui_interface->declare(&fslider14, "2", "");
		ui_interface->declare(&fslider14, "style", "knob");
		ui_interface->declare(&fslider14, "tooltip", "Peak level    in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fslider14, "unit", "dB");
		ui_interface->addVerticalSlider("Eq2 Level", &fslider14, 0.0f, -15.0f, 15.0f, 0.1f);
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fslider16, "1", "");
		ui_interface->declare(&fslider16, "style", "knob");
		ui_interface->declare(&fslider16, "tooltip", "-1 = dry, 1 = wet");
		ui_interface->addVerticalSlider("Dry/Wet Mix", &fslider16, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider17, "2", "");
		ui_interface->declare(&fslider17, "style", "knob");
		ui_interface->declare(&fslider17, "tooltip", "Output scale    factor");
		ui_interface->declare(&fslider17, "unit", "dB");
		ui_interface->addVerticalSlider("Level", &fslider17, 0.0f, -7e+01f, 4e+01f, 0.1f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("attack", &fslider4, 0.3f, 0.0f, 2.0f, 0.1f);
		ui_interface->addHorizontalSlider("decay", &fslider3, 0.3f, 0.0f, 2.0f, 0.1f);
		ui_interface->addHorizontalSlider("frequency", &fslider6, 4.4e+02f, 1e+02f, 2e+03f, 5.0f);
		ui_interface->addHorizontalSlider("gain", &fslider5, 0.9f, 0.0f, 1.0f, 0.05f);
		ui_interface->addButton("gate", &fbutton0);
		ui_interface->addHorizontalSlider("pan", &fslider0, 0.5f, 0.0f, 1.0f, 0.01f);
		ui_interface->addHorizontalSlider("release", &fslider1, 0.3f, 0.0f, 2.0f, 0.1f);
		ui_interface->addHorizontalSlider("sustain", &fslider2, 0.0f, 0.0f, 1e+02f, 2.0f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.001f * float(fslider0));
		float 	fSlow1 = (0.001f * float(fslider1));
		float 	fSlow2 = (0.001f * float(fslider2));
		float 	fSlow3 = float(fbutton0);
		float 	fSlow4 = (0.01f * fSlow3);
		float 	fSlow5 = (0.001f * float(fslider3));
		float 	fSlow6 = (0.001f * float(fslider4));
		int 	iSlow7 = int(((fSlow3 == 0) > 0));
		int 	iSlow8 = (fSlow3 > 0);
		int 	iSlow9 = faustpower<2>(iSlow8);
		int 	iSlow10 = (1 - iSlow8);
		int 	iSlow11 = int((iSlow8 > 0));
		float 	fSlow12 = (0.001f * float(fslider5));
		float 	fSlow13 = (fConst2 * float(fslider6));
		float 	fSlow14 = cosf(fSlow13);
		float 	fSlow15 = sinf(fSlow13);
		float 	fSlow16 = (0 - fSlow15);
		int 	iSlow17 = int((int((fConst3 * float(fslider7))) & 8191));
		float 	fSlow18 = (1.0f / tanf((fConst4 * float(fslider8))));
		float 	fSlow19 = (fSlow18 + 1);
		float 	fSlow20 = (0 - ((1 - fSlow18) / fSlow19));
		float 	fSlow21 = (1.0f / fSlow19);
		float 	fSlow22 = float(fslider9);
		float 	fSlow23 = expf((fConst6 / fSlow22));
		float 	fSlow24 = float(fslider10);
		float 	fSlow25 = ((expf((fConst6 / fSlow24)) / fSlow23) + -1);
		float 	fSlow26 = faustpower<2>(fSlow23);
		float 	fSlow27 = (1.0f - fSlow26);
		float 	fSlow28 = cosf((fConst7 * float(fslider11)));
		float 	fSlow29 = (1.0f - (fSlow28 * fSlow26));
		float 	fSlow30 = (fSlow29 / fSlow27);
		float 	fSlow31 = sqrtf(max((float)0, ((faustpower<2>(fSlow29) / faustpower<2>(fSlow27)) + -1.0f)));
		float 	fSlow32 = (fSlow23 * (fSlow31 + (1.0f - fSlow30)));
		float 	fSlow33 = (fSlow30 - fSlow31);
		float 	fSlow34 = expf((fConst12 / fSlow22));
		float 	fSlow35 = ((expf((fConst12 / fSlow24)) / fSlow34) + -1);
		float 	fSlow36 = faustpower<2>(fSlow34);
		float 	fSlow37 = (1.0f - fSlow36);
		float 	fSlow38 = (1.0f - (fSlow28 * fSlow36));
		float 	fSlow39 = (fSlow38 / fSlow37);
		float 	fSlow40 = sqrtf(max((float)0, ((faustpower<2>(fSlow38) / faustpower<2>(fSlow37)) + -1.0f)));
		float 	fSlow41 = (fSlow34 * (fSlow40 + (1.0f - fSlow39)));
		float 	fSlow42 = (fSlow39 - fSlow40);
		float 	fSlow43 = expf((fConst17 / fSlow22));
		float 	fSlow44 = ((expf((fConst17 / fSlow24)) / fSlow43) + -1);
		float 	fSlow45 = faustpower<2>(fSlow43);
		float 	fSlow46 = (1.0f - fSlow45);
		float 	fSlow47 = (1.0f - (fSlow28 * fSlow45));
		float 	fSlow48 = (fSlow47 / fSlow46);
		float 	fSlow49 = sqrtf(max((float)0, ((faustpower<2>(fSlow47) / faustpower<2>(fSlow46)) + -1.0f)));
		float 	fSlow50 = (fSlow43 * (fSlow49 + (1.0f - fSlow48)));
		float 	fSlow51 = (fSlow48 - fSlow49);
		float 	fSlow52 = expf((fConst22 / fSlow22));
		float 	fSlow53 = ((expf((fConst22 / fSlow24)) / fSlow52) + -1);
		float 	fSlow54 = faustpower<2>(fSlow52);
		float 	fSlow55 = (1.0f - fSlow54);
		float 	fSlow56 = (1.0f - (fSlow28 * fSlow54));
		float 	fSlow57 = (fSlow56 / fSlow55);
		float 	fSlow58 = sqrtf(max((float)0, ((faustpower<2>(fSlow56) / faustpower<2>(fSlow55)) + -1.0f)));
		float 	fSlow59 = (fSlow52 * (fSlow58 + (1.0f - fSlow57)));
		float 	fSlow60 = (fSlow57 - fSlow58);
		float 	fSlow61 = expf((fConst27 / fSlow22));
		float 	fSlow62 = ((expf((fConst27 / fSlow24)) / fSlow61) + -1);
		float 	fSlow63 = faustpower<2>(fSlow61);
		float 	fSlow64 = (1.0f - fSlow63);
		float 	fSlow65 = (1.0f - (fSlow28 * fSlow63));
		float 	fSlow66 = (fSlow65 / fSlow64);
		float 	fSlow67 = sqrtf(max((float)0, ((faustpower<2>(fSlow65) / faustpower<2>(fSlow64)) + -1.0f)));
		float 	fSlow68 = (fSlow61 * (fSlow67 + (1.0f - fSlow66)));
		float 	fSlow69 = (fSlow66 - fSlow67);
		float 	fSlow70 = expf((fConst32 / fSlow22));
		float 	fSlow71 = ((expf((fConst32 / fSlow24)) / fSlow70) + -1);
		float 	fSlow72 = faustpower<2>(fSlow70);
		float 	fSlow73 = (1.0f - fSlow72);
		float 	fSlow74 = (1.0f - (fSlow28 * fSlow72));
		float 	fSlow75 = (fSlow74 / fSlow73);
		float 	fSlow76 = sqrtf(max((float)0, ((faustpower<2>(fSlow74) / faustpower<2>(fSlow73)) + -1.0f)));
		float 	fSlow77 = (fSlow70 * (fSlow76 + (1.0f - fSlow75)));
		float 	fSlow78 = (fSlow75 - fSlow76);
		float 	fSlow79 = expf((fConst37 / fSlow22));
		float 	fSlow80 = ((expf((fConst37 / fSlow24)) / fSlow79) + -1);
		float 	fSlow81 = faustpower<2>(fSlow79);
		float 	fSlow82 = (1.0f - fSlow81);
		float 	fSlow83 = (1.0f - (fSlow28 * fSlow81));
		float 	fSlow84 = (fSlow83 / fSlow82);
		float 	fSlow85 = sqrtf(max((float)0, ((faustpower<2>(fSlow83) / faustpower<2>(fSlow82)) + -1.0f)));
		float 	fSlow86 = (fSlow79 * (fSlow85 + (1.0f - fSlow84)));
		float 	fSlow87 = (fSlow84 - fSlow85);
		float 	fSlow88 = expf((fConst42 / fSlow22));
		float 	fSlow89 = ((expf((fConst42 / fSlow24)) / fSlow88) + -1);
		float 	fSlow90 = faustpower<2>(fSlow88);
		float 	fSlow91 = (1.0f - fSlow90);
		float 	fSlow92 = (1.0f - (fSlow90 * fSlow28));
		float 	fSlow93 = (fSlow92 / fSlow91);
		float 	fSlow94 = sqrtf(max((float)0, ((faustpower<2>(fSlow92) / faustpower<2>(fSlow91)) + -1.0f)));
		float 	fSlow95 = (fSlow88 * (fSlow94 + (1.0f - fSlow93)));
		float 	fSlow96 = (fSlow93 - fSlow94);
		float 	fSlow97 = powf(10,(0.05f * float(fslider12)));
		float 	fSlow98 = float(fslider13);
		float 	fSlow99 = (fConst2 * (fSlow98 / sqrtf(max((float)0, fSlow97))));
		float 	fSlow100 = ((1.0f - fSlow99) / (fSlow99 + 1.0f));
		float 	fSlow101 = ((0 - cosf((fConst2 * fSlow98))) * (fSlow100 + 1));
		float 	fSlow102 = powf(10,(0.05f * float(fslider14)));
		float 	fSlow103 = float(fslider15);
		float 	fSlow104 = (fConst2 * (fSlow103 / sqrtf(max((float)0, fSlow102))));
		float 	fSlow105 = ((1.0f - fSlow104) / (fSlow104 + 1.0f));
		float 	fSlow106 = ((0 - cosf((fConst2 * fSlow103))) * (fSlow105 + 1));
		float 	fSlow107 = (0.001f * float(fslider16));
		float 	fSlow108 = (0.001f * powf(10,(0.05f * float(fslider17))));
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec10[0] = (fSlow0 + (0.999f * fRec10[1]));
			fRec11[0] = (fSlow1 + (0.999f * fRec11[1]));
			fRec13[0] = (fSlow2 + (0.999f * fRec13[1]));
			float fTemp0 = (fSlow4 * fRec13[0]);
			fRec14[0] = (fSlow5 + (0.999f * fRec14[1]));
			fRec15[0] = (fSlow6 + (0.999f * fRec15[1]));
			float fTemp1 = (fConst0 * fRec15[0]);
			float fTemp2 = (fConst0 * (fRec15[0] + fRec14[0]));
			fRec16[0] = ((iSlow7)?0:min(fTemp2, (fRec16[1] + 1)));
			int iTemp3 = int((fRec16[0] < fTemp1));
			fRec12[0] = ((iSlow10 * fRec12[1]) + (iSlow9 * ((iTemp3)?((int((fRec16[0] < 0)))?0:((iTemp3)?(fConst1 * (fRec16[0] / fRec15[0])):1)):((int((fRec16[0] < fTemp2)))?((((fRec16[0] - fTemp1) * (fTemp0 + -1)) / (0 - (fConst0 * (0 - fRec14[0])))) + 1):fTemp0))));
			float fTemp4 = (fConst0 * fRec11[0]);
			fRec17[0] = ((iSlow11)?0:min(fTemp4, (fRec17[1] + 1)));
			fRec18[0] = (fSlow12 + (0.999f * fRec18[1]));
			fRec19[0] = ((fSlow15 * fRec20[1]) + (fSlow14 * fRec19[1]));
			fRec20[0] = (((fSlow14 * fRec20[1]) + (fSlow16 * fRec19[1])) + (1 - iVec0[1]));
			float fTemp5 = ((fRec19[0] * fRec18[0]) * ((int((fRec17[0] < 0)))?fRec12[0]:((int((fRec17[0] < fTemp4)))?(fRec12[0] + (fConst1 * ((fRec17[0] * (0 - fRec12[0])) / fRec11[0]))):0)));
			float fTemp6 = (fTemp5 * fRec10[0]);
			fVec1[IOTA&8191] = (fSlow3 * fTemp6);
			float fTemp7 = (0.3f * fVec1[(IOTA-iSlow17)&8191]);
			fRec22[0] = ((fSlow21 * (fRec7[1] + fRec7[2])) + (fSlow20 * fRec22[1]));
			fRec21[0] = ((fSlow33 * fRec21[1]) + (fSlow32 * (fRec7[1] + (fSlow25 * fRec22[0]))));
			fVec2[IOTA&16383] = ((0.35355338f * fRec21[0]) + 1e-20f);
			float fTemp8 = (((0.6f * fRec8[1]) + fVec2[(IOTA-iConst9)&16383]) - fTemp7);
			fVec3[IOTA&1023] = fTemp8;
			fRec8[0] = fVec3[(IOTA-iConst10)&1023];
			float 	fRec9 = (0 - (0.6f * fVec3[IOTA&1023]));
			float fTemp9 = (fRec8[1] + fRec9);
			fRec26[0] = ((fSlow21 * (fRec3[1] + fRec3[2])) + (fSlow20 * fRec26[1]));
			fRec25[0] = ((fSlow42 * fRec25[1]) + (fSlow41 * (fRec3[1] + (fSlow35 * fRec26[0]))));
			fVec4[IOTA&16383] = ((0.35355338f * fRec25[0]) + 1e-20f);
			float fTemp10 = (((0.6f * fRec23[1]) + fVec4[(IOTA-iConst14)&16383]) - fTemp7);
			fVec5[IOTA&2047] = fTemp10;
			fRec23[0] = fVec5[(IOTA-iConst15)&2047];
			float 	fRec24 = (0 - (0.6f * fVec5[IOTA&2047]));
			float fTemp11 = (fRec24 + (fRec23[1] + fTemp9));
			fRec30[0] = ((fSlow21 * (fRec5[1] + fRec5[2])) + (fSlow20 * fRec30[1]));
			fRec29[0] = ((fSlow51 * fRec29[1]) + (fSlow50 * (fRec5[1] + (fSlow44 * fRec30[0]))));
			fVec6[IOTA&8191] = ((0.35355338f * fRec29[0]) + 1e-20f);
			float fTemp12 = (fVec6[(IOTA-iConst19)&8191] + (fTemp7 + (0.6f * fRec27[1])));
			fVec7[IOTA&2047] = fTemp12;
			fRec27[0] = fVec7[(IOTA-iConst20)&2047];
			float 	fRec28 = (0 - (0.6f * fVec7[IOTA&2047]));
			fRec34[0] = ((fSlow21 * (fRec1[1] + fRec1[2])) + (fSlow20 * fRec34[1]));
			fRec33[0] = ((fSlow60 * fRec33[1]) + (fSlow59 * (fRec1[1] + (fSlow53 * fRec34[0]))));
			fVec8[IOTA&16383] = ((0.35355338f * fRec33[0]) + 1e-20f);
			float fTemp13 = (fVec8[(IOTA-iConst24)&16383] + (fTemp7 + (0.6f * fRec31[1])));
			fVec9[IOTA&2047] = fTemp13;
			fRec31[0] = fVec9[(IOTA-iConst25)&2047];
			float 	fRec32 = (0 - (0.6f * fVec9[IOTA&2047]));
			float fTemp14 = (fRec32 + (fRec31[1] + (fRec28 + (fRec27[1] + fTemp11))));
			float fTemp15 = (fTemp5 * (1 - fRec10[0]));
			fVec10[IOTA&8191] = (fSlow3 * fTemp15);
			float fTemp16 = (0.3f * fVec10[(IOTA-iSlow17)&8191]);
			fRec38[0] = ((fSlow21 * (fRec6[1] + fRec6[2])) + (fSlow20 * fRec38[1]));
			fRec37[0] = ((fSlow69 * fRec37[1]) + (fSlow68 * (fRec6[1] + (fSlow62 * fRec38[0]))));
			fVec11[IOTA&8191] = ((0.35355338f * fRec37[0]) + 1e-20f);
			float fTemp17 = (fVec11[(IOTA-iConst29)&8191] - ((0.6f * fRec35[1]) + fTemp16));
			fVec12[IOTA&1023] = fTemp17;
			fRec35[0] = fVec12[(IOTA-iConst30)&1023];
			float 	fRec36 = (0.6f * fVec12[IOTA&1023]);
			fRec42[0] = ((fSlow21 * (fRec2[1] + fRec2[2])) + (fSlow20 * fRec42[1]));
			fRec41[0] = ((fSlow78 * fRec41[1]) + (fSlow77 * (fRec2[1] + (fSlow71 * fRec42[0]))));
			fVec13[IOTA&8191] = ((0.35355338f * fRec41[0]) + 1e-20f);
			float fTemp18 = (fVec13[(IOTA-iConst34)&8191] - (fTemp16 + (0.6f * fRec39[1])));
			fVec14[IOTA&2047] = fTemp18;
			fRec39[0] = fVec14[(IOTA-iConst35)&2047];
			float 	fRec40 = (0.6f * fVec14[IOTA&2047]);
			fRec46[0] = ((fSlow21 * (fRec4[1] + fRec4[2])) + (fSlow20 * fRec46[1]));
			fRec45[0] = ((fSlow87 * fRec45[1]) + (fSlow86 * (fRec4[1] + (fSlow80 * fRec46[0]))));
			fVec15[IOTA&8191] = ((0.35355338f * fRec45[0]) + 1e-20f);
			float fTemp19 = ((fTemp16 + fVec15[(IOTA-iConst39)&8191]) - (0.6f * fRec43[1]));
			fVec16[IOTA&2047] = fTemp19;
			fRec43[0] = fVec16[(IOTA-iConst40)&2047];
			float 	fRec44 = (0.6f * fVec16[IOTA&2047]);
			fRec50[0] = ((fSlow21 * (fRec0[1] + fRec0[2])) + (fSlow20 * fRec50[1]));
			fRec49[0] = ((fSlow96 * fRec49[1]) + (fSlow95 * (fRec0[1] + (fSlow89 * fRec50[0]))));
			fVec17[IOTA&8191] = ((0.35355338f * fRec49[0]) + 1e-20f);
			float fTemp20 = ((fTemp16 + fVec17[(IOTA-iConst44)&8191]) - (0.6f * fRec47[1]));
			fVec18[IOTA&1023] = fTemp20;
			fRec47[0] = fVec18[(IOTA-iConst45)&1023];
			float 	fRec48 = (0.6f * fVec18[IOTA&1023]);
			fRec0[0] = (fRec48 + (fRec47[1] + (fRec44 + (fRec43[1] + (fRec40 + (fRec39[1] + (fRec36 + (fRec35[1] + fTemp14))))))));
			fRec1[0] = ((fRec48 + (fRec47[1] + (fRec44 + (fRec43[1] + (fRec40 + (fRec39[1] + (fRec35[1] + fRec36))))))) - fTemp14);
			float fTemp21 = (fRec32 + (fRec31[1] + (fRec27[1] + fRec28)));
			fRec2[0] = ((fRec48 + (fRec47[1] + (fRec44 + (fRec43[1] + fTemp21)))) - (fRec40 + (fRec39[1] + (fRec36 + (fRec35[1] + fTemp11)))));
			fRec3[0] = ((fRec48 + (fRec47[1] + (fRec44 + (fRec43[1] + fTemp11)))) - (fRec40 + (fRec39[1] + (fRec36 + (fRec35[1] + fTemp21)))));
			float fTemp22 = (fRec28 + (fRec27[1] + fTemp9));
			float fTemp23 = (fRec23[1] + fRec24);
			float fTemp24 = (fRec32 + (fRec31[1] + fTemp23));
			fRec4[0] = ((fRec48 + (fRec47[1] + (fRec40 + (fRec39[1] + fTemp24)))) - (fRec44 + (fRec43[1] + (fRec36 + (fRec35[1] + fTemp22)))));
			fRec5[0] = ((fRec48 + (fRec47[1] + (fRec40 + (fRec39[1] + fTemp22)))) - (fRec44 + (fRec43[1] + (fRec36 + (fRec35[1] + fTemp24)))));
			float fTemp25 = (fRec28 + (fRec27[1] + fTemp23));
			float fTemp26 = (fRec32 + (fRec31[1] + fTemp9));
			fRec6[0] = ((fRec48 + (fRec47[1] + (fRec36 + (fRec35[1] + fTemp26)))) - (fRec44 + (fRec43[1] + (fRec40 + (fRec39[1] + fTemp25)))));
			fRec7[0] = ((fRec48 + (fRec47[1] + (fRec36 + (fRec35[1] + fTemp25)))) - (fRec44 + (fRec43[1] + (fRec40 + (fRec39[1] + fTemp26)))));
			float fTemp27 = (0.37f * (fRec1[0] + fRec2[0]));
			float fTemp28 = (fSlow101 * fRec51[1]);
			fRec51[0] = (fTemp27 - (fTemp28 + (fSlow100 * fRec51[2])));
			float fTemp29 = (fTemp28 + fRec51[2]);
			float fTemp30 = (fSlow100 * fRec51[0]);
			float fTemp31 = (0.5f * ((fTemp30 + (fTemp27 + fTemp29)) + (fSlow97 * ((fTemp30 + fTemp29) - fTemp27))));
			float fTemp32 = (fSlow106 * fRec52[1]);
			fRec52[0] = (fTemp31 - (fTemp32 + (fSlow105 * fRec52[2])));
			float fTemp33 = ((fSlow105 * fRec52[0]) + (fTemp32 + fRec52[2]));
			fRec53[0] = (fSlow107 + (0.999f * fRec53[1]));
			float fTemp34 = (fRec53[0] + 1.0f);
			float fTemp35 = (1.0f - (0.5f * fTemp34));
			fRec54[0] = (fSlow108 + (0.999f * fRec54[1]));
			output0[i] = (FAUSTFLOAT)(0.5f * (fRec54[0] * ((fSlow3 * (fTemp15 * fTemp34)) + (fTemp35 * ((fTemp31 + fTemp33) + (fSlow102 * (fTemp33 - fTemp31)))))));
			float fTemp36 = (0.37f * (fRec1[0] - fRec2[0]));
			float fTemp37 = (fSlow101 * fRec55[1]);
			fRec55[0] = (fTemp36 - (fTemp37 + (fSlow100 * fRec55[2])));
			float fTemp38 = (fTemp37 + fRec55[2]);
			float fTemp39 = (fSlow100 * fRec55[0]);
			float fTemp40 = (0.5f * ((fTemp39 + (fTemp36 + fTemp38)) + (fSlow97 * ((fTemp39 + fTemp38) - fTemp36))));
			float fTemp41 = (fSlow106 * fRec56[1]);
			fRec56[0] = (fTemp40 - (fTemp41 + (fSlow105 * fRec56[2])));
			float fTemp42 = ((fSlow105 * fRec56[0]) + (fTemp41 + fRec56[2]));
			output1[i] = (FAUSTFLOAT)(0.5f * (fRec54[0] * ((fSlow3 * (fTemp6 * fTemp34)) + (fTemp35 * ((fTemp40 + fTemp42) + (fSlow102 * (fTemp42 - fTemp40)))))));
			// post processing
			fRec56[2] = fRec56[1]; fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1]; fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1]; fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1]; fRec51[1] = fRec51[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec47[1] = fRec47[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec43[1] = fRec43[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec42[1] = fRec42[0];
			fRec35[1] = fRec35[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec31[1] = fRec31[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec8[1] = fRec8[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			IOTA = IOTA+1;
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec12[1] = fRec12[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			iVec0[1] = iVec0[0];
		}
	}
};


