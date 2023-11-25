// the server side
#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <sstream>
#include <iomanip> // for the std::setw i think


#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x9876
#define SAMPLE_METHOD_ID 0x6666

std::shared_ptr<vsomeip::application> app ; 


void on_message(const std::shared_ptr<vsomeip::message> &_request)
{
std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload(); 
vsomeip::length_t l = its_payload->get_length(); 


// get the actual payload from the client 

std::stringstream ss ; 
for (vsomeip::length_t i=0 ; i < l ;i++)
{
	ss << std::setw(2)<< std::setfill('0') << std::hex << (int)*its_payload->get_data()+i << " " << std::endl; 
}

std::cout << "SERVER : received message from the client/session [" 
							    << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
							    << std::setw(4) << std::setfill('0') << std::hex << _request->get_session() << "]"
							    << ss.str() <<std::endl ; 




// ok the server received some message/request from the client , now it will respond

std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request); 
its_payload = vsomeip::runtime::get()->create_payload() ; 
std::vector <vsomeip::byte_t> its_payload_data ; 

for (int i = 9 ; i >= 0; i--)
	{
	its_payload_data.push_back(i % 256); 
	}

its_payload->set_data(its_payload_data); 
its_response->set_payload(its_payload); 
app->send(its_response,true); 
std::cout << "from server to client" << std::endl; 
}


int main ()
{

app = vsomeip::runtime::get()->create_application("Server"); 
app->init(); 
// when a message is received from a client, on_message function is run
app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID,SAMPLE_METHOD_ID, on_message);
// offer the service with a service id and an instance id
app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID); 
// start listening to requests from clients 
app->start();

return(0); 
}


