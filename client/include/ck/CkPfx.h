// CkPfx.h: interface for the CkPfx class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkPfx_H
#define _CkPfx_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkMultiByteBase.h"

class CkCert;
class CkPrivateKey;
class CkCertChain;
class CkByteData;
class CkJavaKeyStore;
class CkXmlCertVault;



#ifndef __sun__
#pragma pack (push, 8)
#endif
 

// CLASS: CkPfx
class CK_VISIBLE_PUBLIC CkPfx  : public CkMultiByteBase
{
    private:
	

	// Don't allow assignment or copying these objects.
	CkPfx(const CkPfx &);
	CkPfx &operator=(const CkPfx &);

    public:
	CkPfx(void);
	virtual ~CkPfx(void);

	static CkPfx *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The number of certificates contained in the PFX.
	int get_NumCerts(void);

	// The number of private keys contained in the PFX.
	int get_NumPrivateKeys(void);



	// ----------------------
	// Methods
	// ----------------------
	// Adds a certificate, its private key (if it exists), and potentially its
	// certificate chain to the PFX. If ARG2 is true, then the certificate must have
	// a private key. The certificate's private key is automatically obtained
	// (internally) via the ARG1's ExportPrivateKey method. If the certificate's chain
	// of authentication is to be added, it is automatically constructed and added
	// using whatever resources are at hand (such as certs provided via the
	// UseCertVault method, the trusted roots from Chilkat's TrustedRoots class, etc.
	// If a certificate chain is to be added, which is the typical case, then the chain
	// must be completed to the root to succeed.
	bool AddCert(CkCert &cert, bool includeChain);

	// Adds a private key and certificate chain to the PFX. The private key should be
	// such that it is associated with the 1st certificate in the chain. In other
	// words, the 1st certificate in the chain has a public key (embedded within the
	// X.509 structure of the cert itself) that is the counterpart to the private key.
	bool AddPrivateKey(CkPrivateKey &privKey, CkCertChain &certChain);

	// Returns the Nth certificate in the PFX. (The 1st certificate is at index 0.)
	// The caller is responsible for deleting the object returned by this method.
	CkCert *GetCert(int index);

	// Returns the Nth private key in the PFX. (The 1st private key is at index 0.)
	// The caller is responsible for deleting the object returned by this method.
	CkPrivateKey *GetPrivateKey(int index);

	// Loads a PFX from in-memory bytes.
	bool LoadPfxBytes(const CkByteData &pfxData, const char *password);

	// Loads a PFX from encoded byte data. The ARG2 can by any encoding, such as
	// "Base64", "modBase64", "Base32", "UU", "QP" (for quoted-printable), "URL" (for
	// url-encoding), "Hex", "Q", "B", "url_oath", "url_rfc1738", "url_rfc2396", and
	// "url_rfc3986".
	bool LoadPfxEncoded(const char *encodedData, const char *encoding, const char *password);

	// Loads a PFX from a file.
	bool LoadPfxFile(const char *path, const char *password);

	// Write the PFX to in-memory bytes.
	bool ToBinary(const char *password, CkByteData &outBytes);

	// Write the PFX to an encoded string. The ARG2 can be any encoding such as
	// "base64" or "hex".
	bool ToEncodedString(const char *password, const char *encoding, CkString &outStr);
	// Write the PFX to an encoded string. The ARG2 can be any encoding such as
	// "base64" or "hex".
	const char *toEncodedString(const char *password, const char *encoding);

	// Write the PFX to a file. PFX and PKCS12 are essentially the same. Standard
	// filename extensions are ".pfx" or ".p12".
	bool ToFile(const char *password, const char *path);

	// Converts the PFX (PKCS12) to a JavaKeyStore object. One JKS entry per private
	// key found in the PKCS12 is added. The certs found within the PCKS12 are used to
	// build the certificate chains for each private key. (A typical PFX file contains
	// a single private key along with its associated certificate, and the certificates
	// in the chain of authentication to the root CA cert.)
	// 
	// The specified alias is applied to the 1st private key found. If the alias is
	// empty, then the alias is obtained from the cert/PFX in the following order of
	// preference:
	//     Certificate's subject common name
	//     Certificate's subject email address
	//     Certificate's friendly name found in the PKCS9 attributes of the PKCS12
	//     Certificate's serial number
	// 
	// If multiple private keys are found in the PKCS12, then all but the first will
	// automaticallly be assigned aliases using the preference just described.
	// 
	// The caller is responsible for deleting the object returned by this method.
	CkJavaKeyStore *ToJavaKeyStore(const char *alias, const char *password);

	// Adds an XML certificate vault to the object's internal list of sources to be
	// searched for certificates for help in building certificate chains to a root
	// certificate.
	bool UseCertVault(CkXmlCertVault &vault);





	// END PUBLIC INTERFACE


};
#ifndef __sun__
#pragma pack (pop)
#endif


	
#endif
