#include "http_layer.h"

CHTTPRequest::CHTTPRequest ( string & header )
 {
 	m_Header.assign ( header );
 }