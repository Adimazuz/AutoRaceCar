#include <string>
#include "ISerial.h"
#include "bitcraze_types.h"


class Bitcraze
{

public:
    /**
     * connects to Arduino controller
     */
     bool connect() ;
		
	 /**
     * @return true if connected 
     */
     bool isConnected(){return m_serial->isConnected();}
	 /**
     * send request to arduino to start sending data from flow sensor
     * @return this
     */
     Bitcraze &requestFlowData();
	 /**
     * send request to arduino to stop sending data from flow sensor
     * @return this
     */
     Bitcraze &stopStream();
	 /**
     * reads the flow sensor data sent from the Arduino
     * @return Flow 
     */
     Flow getFlowOutput() ;


    ~Bitcraze()= default;

     Bitcraze() = default;

private:

    std::shared_ptr<ISerial> m_serial;
    bool _is_connected;
};
