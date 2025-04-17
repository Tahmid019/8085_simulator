#include "../Headers/Head_1.h"
#include "../Headers/utils.h"

void message(std::string msg="[--] ", uint8_t in_load = 0, uint8_t out_load = 0, MessageType type = MessageType::INFO) {
    std::string prefix;
    switch (type) {
        case MessageType::INFO: {
            prefix = "[INFO] ";
            std::cout << prefix << msg << std::endl;
            break;
        }
        case MessageType::WARNING: {
            prefix = "[WARNING] ";
            std::cout << prefix << msg << std::endl;
            break;
        }
        case MessageType::ERROR: {
            prefix = "[ERROR] ";
            std::cout << prefix << msg << std::endl;
        }
        case MessageType::MEMORY: {
            prefix = "[MEMORY - Load] ";
            std::cerr << prefix << msg << " Memory-value: [ " << std::hex << static_cast<int>(in_load) << " ]";
            break;
        }
        case MessageType::REGISTER: {
            prefix = "[REGISTER - Load] ";
            std::cerr << prefix << msg << " Register-value: [ " << std::hex << static_cast<int>(in_load) << " ]";
            break;
        }
    }   

    if (out_load != 0x00) std::cout << " <-- [ " << std::hex << static_cast<int>(out_load) << " ]";
    std::cout << std::endl;
}

void debug(std::string msg = "[--] ", uint16_t in_addr = 0, uint8_t in_data = 0, MessageType type = MessageType::INFO) {
    std::string prefix;
    switch (type) {
        case MessageType::INFO: {
            prefix = "[INFO] ";
            std::cout << prefix << msg << std::endl;
            break;
        }
        case MessageType::MEMORY: {
            prefix = "[MEMORY] ";
            std::cout << prefix << msg;
            if (in_addr != 0) std::cout << " Address: { " << std::hex << static_cast<uint16_t>(in_addr) << " } ";
            if (in_data != 0) std::cout << " Data : [ " << std::hex << static_cast<int>(in_data) << " ] ";
            std::cout << std::endl;
            break;
        }
        case MessageType::REGISTER: {
            prefix = "[REGISTER] ";
            std::cout << prefix << msg;
            if (in_addr != 0) std::cout << " Address: { " << std::hex << static_cast<uint16_t>(in_addr) << " } ";
            if (in_data != 0) std::cout << " Data : [ " << std::hex << static_cast<int>(in_data) << " ] ";
            std::cout << std::endl;
            break;
        }
        default: {
            std::cout << "[UNKNOWN CASE]" << std::endl;
            break;
        }
    }
}

bool carry(uint8_t value) {
    return ((static_cast<int>(value) / 255) != 0);
}// Wrong Imp

size_t t2t_message(string custm_message = "", uint16_t a = 0XFFFF, uint16_t b = 0XFFFF, Type2Tpe type = Type2Tpe::t8_2_8) {
	string message = "";
    switch (type) {
	    case Type2Tpe::t8_2_8: {
		    message = "Display { 8bit-8bit } >> ";
		    a = (static_cast<uint8_t>(a));
		    b = (static_cast<uint8_t>(b));
		    break;
	    }
		case Type2Tpe::t8_2_16: {
			message = "Display { 8bit-16bit } >> ";
			a = (static_cast<uint8_t>(a));
			b = (static_cast<uint16_t>(b));
			break;
		}
        case Type2Tpe::t16_2_8: {
            message = "Display { 16bit-8bit } >> ";
            a = (static_cast<uint16_t>(a));
            b = (static_cast<uint8_t>(b));
            break;
        }
		case Type2Tpe::t16_2_16: {
			message = "Display { 16bit-16bit } >> ";
			a = (static_cast<uint16_t>(a));
			b = (static_cast<uint16_t>(b));
			break;
		}
        default: {
            message = "Display { UNKNOWN } >> ";
            a = (static_cast<uint16_t>(a));
            b = (static_cast<uint16_t>(b));
            break;
        }
    };
    cout << custm_message << endl;
	cout << message << "a: { " << std::hex << a << " } b: { " << std::hex << b << " }" << endl;

	return custm_message.length() + message.length() + 1;
}
void removeTrailingSpaces(string& str) {
    while (str.size() > 0 && str.back() == ' ')str.pop_back();
    reverse(str.begin(), str.end());
    while (str.size() > 0 && str.back() == ' ')str.pop_back();
    reverse(str.begin(), str.end());
}