#include <sstream>
#include <string>

enum algorithmType {AES, tDES};
enum blockEncodingType {ECB, CBC, OFB};

class stateObjectType {
	private:
	bool encrypting;
	algorithmType algo;
	blockEncodingType encoding;
	std::stringstream content;
	std::string key;
	~stateObjectType();
	public:
	stateObjectType(bool e, algorithmType a, blockEncodingType b, std::string c, std::string k)
		: encrypting(e), algo(a), encoding(b), key(k) {
			content.str(c);
	}
	std::string process();
};