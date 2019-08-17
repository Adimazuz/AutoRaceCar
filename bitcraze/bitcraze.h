#include <string>
#include "ISerial.h"
#include "bitcraze_types.h"


class Bitcraze
{

public:
    /*
     * connects to Arduino controller
     */
     bool connect() ;
	
     Bitcraze &requestFlowData();

     Bitcraze &stopStream();
	 
     Flow getFlowOutput() ;

    ~Bitcraze()= default;

     Bitcraze() = default;

private:

    std::shared_ptr<ISerial> m_serial;
    bool _is_connected;
};
