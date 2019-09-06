#include <iostream>
#include <vector>
#include <math.h>
#include "bitcraze.h"

using std::string;

#define SENSOR_RESULUTION 30*30
#define FIELD_OF_VIEW 42
#define SCALAR 1


bool Bitcraze::connect()
{
    m_serial = ISerial::create();
    _is_connected =  m_serial->connect();
    return _is_connected;

}

Bitcraze& Bitcraze::requestFlowData(){
//   m_serial->write("#");

    m_serial->write(START_STREAMING);
}

Bitcraze &Bitcraze::stopStream()
{
    m_serial->write(STOP_STREAMING);

}

Flow Bitcraze::getFlowOutput()
{
    Flow output = {};
    m_serial->read(reinterpret_cast<char*>(&output), sizeof(Flow));
	
	//int x_distance = calcDistance(output.deltaX);
    return output;
}

Bitcraze &Bitcraze::flush()
{
    m_serial->flush();
}

//==========================private==================================

//int Bitcraze::calcDistance(int sensor_value,int range){
//	return ( (sensor_value * range) / (SENSOR_RESULUTION * SCALAR ) ) * 2 * tan(FIELD_OF_VIEW/2);
//}

