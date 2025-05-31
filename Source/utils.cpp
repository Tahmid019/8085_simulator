#include "../Headers/Head_1.h"
#include "../Headers/utils.h"

void message(string msg="[--] ", uint8_t in_load = 0, uint8_t out_load = 0, MessageType type = MessageType::INFO) {
    string prefix;
    switch (type) {
        case MessageType::INFO: {
            prefix = "[INFO] ";
            cout << prefix << msg << endl;
            break;
        }
        case MessageType::WARNING: {
            prefix = "[WARNING] ";
            cout << prefix << msg << endl;
            break;
        }
        case MessageType::ERROR: {
            prefix = "[ERROR] ";
            cout << prefix << msg << endl;
        }
        case MessageType::MEMORY: {
            prefix = "[MEMORY - Load] ";
            cerr << prefix << msg << " Memory-value: [ " << hex << static_cast<int>(in_load) << " ]";
            break;
        }
        case MessageType::REGISTER: {
            prefix = "[REGISTER - Load] ";
            cerr << prefix << msg << " Register-value: [ " << hex << static_cast<int>(in_load) << " ]";
            break;
        }
    }   

    if (out_load != 0x00) cout << " <-- [ " << hex << static_cast<int>(out_load) << " ]";
    cout << endl;
}

void debug(string msg = "[--] ", uint16_t in_addr = 0, uint8_t in_data = 0, MessageType type = MessageType::INFO) {
    string prefix;
    switch (type) {
        case MessageType::INFO: {
            prefix = "[INFO] ";
            cout << prefix << msg << endl;
            break;
        }
        case MessageType::MEMORY: {
            prefix = "[MEMORY] ";
            cout << prefix << msg;
            if (in_addr != 0) cout << " Address: { " << hex << static_cast<uint16_t>(in_addr) << " } ";
            if (in_data != 0) cout << " Data : [ " << hex << static_cast<int>(in_data) << " ] ";
            cout << endl;
            break;
        }
        case MessageType::REGISTER: {
            prefix = "[REGISTER] ";
            cout << prefix << msg;
            if (in_addr != 0) cout << " Address: { " << hex << static_cast<uint16_t>(in_addr) << " } ";
            if (in_data != 0) cout << " Data : [ " << hex << static_cast<int>(in_data) << " ] ";
            cout << endl;
            break;
        }
        default: {
            cout << "[UNKNOWN CASE]" << endl;
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
	cout << message << "a: { " << hex << a << " } b: { " << hex << b << " }" << endl;

	return custm_message.length() + message.length() + 1;
}
void removeTrailingSpaces(string& str) {
    while (str.size() > 0 && (str.back() == ' '||str.back()=='\t'))str.pop_back();
    reverse(str.begin(), str.end());
    while (str.size() > 0 && (str.back() == ' '||str.back()=='\t'))str.pop_back();
    reverse(str.begin(), str.end());
}

void trim(string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        s.clear();
        return;
    }
    size_t end = s.find_last_not_of(" \t\r\n");
    s = s.substr(start, end - start + 1);
}


string toUpper(const string& input) {
    string result = input;
    for (char& c : result) {
        c = toupper(static_cast<unsigned char>(c));
    }
    return result;
}

