#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <iomanip>
#include <condition_variable>
#include <thread>
#include <sstream>


#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x9876
#define SAMPLE_METHOD_ID 0x6666



std::shared_ptr< vsomeip::application > app;
std::mutex mutex ; 
std::condition_variable condition ; 



void on_availability(vsomeip::service_t _service, 
		     vsomeip::instance_t _instance , 
	             bool _is_available)
{

	std::cout << "CLIENT:  service [" << std::setw(4)<< std::setfill('0') << std::hex << _service << "." << _instance << "] is " 
                  << (_is_available? "available. ": "NOT available.") << std::endl;

	// if the service is available then this will notify the run() function and then we can construct the message and send it 
	condition.notify_one() ; 
}


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

	std::cout << "CLIENT : received message from the client/session [" 
								    << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
								    << std::setw(4) << std::setfill('0') << std::hex << _request->get_session() << "]"
								    << ss.str() <<std::endl ; 




}



void run() {



  std::unique_lock<std::mutex> its_lock(mutex);
  condition.wait(its_lock);

  std::shared_ptr< vsomeip::message> request;
  request = vsomeip::runtime::get()->create_request();
  request->set_service(SAMPLE_SERVICE_ID);
  request->set_instance(SAMPLE_INSTANCE_ID);
  request->set_method(SAMPLE_METHOD_ID);

  std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
  std::vector< vsomeip::byte_t > its_payload_data;
  for (vsomeip::byte_t i=0; i<10; i++) {
      its_payload_data.push_back(i % 256);
  }
  its_payload->set_data(its_payload_data);
  request->set_payload(its_payload);
//for (;;){
  app->send(request, true);
std::cout << "from client to server" << std::endl; 
//}
}




int main() {

    app = vsomeip::runtime::get()->create_application("client");
    app->init();
    // when a service from a particular server is available 
    // this client knows it and calls on availability method
    app->register_availability_handler(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID,on_availability); 
    // request the service 
    app->request_service(SAMPLE_SERVICE_ID,SAMPLE_INSTANCE_ID); 
    // when a messag is received, this his the method that processes it 
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message); 
//The app has to be started before we handle messages , because a running event loop to process the messages 
// --> wait till we receive a message with a mutex (service available) and then send the mes 
    std::thread sender(run); 
    app->start();
}
