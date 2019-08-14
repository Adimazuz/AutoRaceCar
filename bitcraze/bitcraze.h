#include <string>
#include "ISerial.h"


class Bitcraze
{

public:
    /*
     * connects to Arduino controller
     */
     bool connect() ;
	
     Bitcraze &requestFlowData();
	 
     Flow getFlowOutput() ;

	~Bitcraze();

     Bitcraze() = default;

private:

    std::shared_ptr<ISerial> m_serial;
    bool _is_connected = false;
};
