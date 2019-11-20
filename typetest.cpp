#include "pxt.h"
#include "MicroBit.h"

#include "Utils.h"

using namespace pxt;

namespace tt {


void logln() {
	 log("\r\n");
}

void logRColl(RefCollection &rColl) {
	 char buf[30];
	 log("rColl(");
	 for (int i=0; i<rColl.length(); i++) {
		 if (i==0) {
			 uBit.serial.send("(");
		 } else {
			 uBit.serial.send(",");
		 }
		 float2char(buf, toFloat(rColl.getAt(i)), 2);
		 log(buf);
	 }
	 log(")");
}


	//% blockId=tt_test
	//% block="Test"
	//% shim=tt::test
	void test() {
	    uBit.serial.send("CALL: test()\r\n");
		uBit.display.scroll("cpp-tt-test");
	}

//	static char *buf = 0;
//
//	void cleanup() {
//		if (buf != 0) {
//			delete buf;
//			buf = 0;
//		}
//	}

	//% blockId=tt_show
	//% block="Show"
	//% shim=tt::show
	void show(String text) {
	    uBit.serial.send("CALL: show(...)\r\n");
		const char *msg = PXT_STRING_DATA(text);
	    uBit.serial.printf("show(%s)\r\n", msg);
		uBit.display.scroll(msg);
	}


	static int cnt = 0;

	void writeHex(int8_t b) {
		uBit.serial.printf(" %x", b);
	}

	//% blockId=tt_gettime
	//% block="Current Time"
	//% shim=tt::gettime
	String gettime() {
	    uBit.serial.send("CALL: gettime()\r\n");

	    char buf[30];
	    cnt += 1;
	    sprintf(buf, "cpp-%d", cnt);
	    return mkString(buf);
	}

	//% blockId=tt_sumvec
	//% block="Sum Vec|number[] %vec"
	//% shim=tt::sumvec
	TNumber sumvec(RefCollection &arr) {
	    uBit.serial.send("CALL: sumvec()\r\n");
	    int len = arr.length();
	    uBit.serial.printf("len: %d\r\n", len);
	    float result = 0.0f;
	    for (int i=0; i<len; i++) {
		    TNumber tn = arr.getAt(i);
			float f = toFloat(tn);
			result += f;
	    }
	    return fromFloat(result);
	}

	//% blockId=tt_addvec
	//% block="Add Vec|number[] %vec1|number[] %vec2"
	//% shim=tt::addvec
	RefCollection addvec(RefCollection &vec1, RefCollection &vec2) {
	    uBit.serial.send("CALL: addvec() \r\n");
	    logRColl(vec1);
	    logRColl(vec2);
	    int len1 = vec1.length();
	    int len2 = vec2.length();
	    RefCollection result;
	    if (len1 != len2) {
		    uBit.serial.printf("different vector sizes: %d and %d\r\n", len1, len2);
		    return result;
	    }
//	    RefCollection *result = Array_::mk();
	    for (int i=0; i<len1; i++) {
	    	float v1 = toFloat(vec1.getAt(i));
	    	float v2 = toFloat(vec2.getAt(i));
	    	float vr = v1 + v2;
//		    Array_::insertAt(result, i, fromFloat(vr));
	    	result.head.push(fromFloat(vr));
	    }
	    logRColl(result);
	    return result;
	}


	//% blockId=tt_logvec
	//% block="Log Vec|number[] %vec"
	//% shim=tt::logvec
	void logvec(RefCollection &vec) {
		char buf[30];
	    int len = vec.length();
	    log("rColl(");
	    for (int i=0; i<len; i++) {
	    	float v = toFloat(vec.getAt(i));
			 if (i==0) {
				 log("(");
			 } else {
				 log(",");
			 }
			 float2char(buf, toFloat(vec.getAt(i)), 2);
			 log(buf);
		 }
		 log(")");
//		 vec.head.set(1, fromFloat(3.3f));
	}


    /**
     * log a number.
     * @param num number to display, eg: 1.5
     */
     //% weight=92 blockGap=8
     //% block="Log Number|number %num"
     //% blockId=tt_logNumber
     //% shim=tt::logNumber
     void logNum(float num) {
    	 logFloat(num);
     }

}
