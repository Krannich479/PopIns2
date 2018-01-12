/*!
* \file    src/CDBG_Data_extension.h
* \brief   Library for extending the functionality of the CompactedDBG by implementing the data wrapper CDBG_Data_t
*
*/
#ifndef CDBG_EXTENSION_H_
#define CDBG_EXTENSION_H_


// =========================
// Includes
// =========================
#include <bifrost/CompactedDBG.hpp>     /* has the CDBG_Data_t template */


// =========================
// Structs
// =========================
/*!
* \class        UnitigExtension
* \headerfile   src/CDBG_Data_extension.h
* \brief        Struct extending the functionality of the CompactedDBG.
* \details      The struct has to inherit from the CDBG_Data_t struct and implement at least all its virtual functions.
* \ref          https://github.com/pmelsted/bfgraph/blob/master/src/CompactedDBG.hpp
*/
struct UnitigExtension : public CDBG_Data_t<UnitigExtension> {

    private:
        unsigned ID;

    public:
        unsigned getConnectedcomponent() const {return ID;}
        void setConnectedcomponent(const unsigned cc) {ID = cc;}

        void join(const UnitigMap<UnitigExtension>& um_dest, const UnitigMap<UnitigExtension>& um_src);
        void sub(const UnitigMap<UnitigExtension>& um_src, UnitigExtension& new_data, const bool last_extraction) const;

};



#endif /*CDBG_EXTENSION_H_*/