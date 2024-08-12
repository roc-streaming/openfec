/* $Id: of_codec_profile.h 199 2014-10-21 14:25:02Z roca $ */
/*
 * OpenFEC.org AL-FEC Library.
 * (c) Copyright 2009 - 2012 INRIA - All rights reserved
 * Contact: vincent.roca@inria.fr
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 */


/****** GENERAL SETUP OPTIONS; EDIT AS APPROPRIATE ****************************/

#include "../../lib_common/of_build_config.h"

#ifdef OF_DEBUG
/* additional parameter for memory statistic purposes */
#define	MEM_STATS_ARG	,ofcb->stats
#define MEM_STATS ,stats
#else
#define MEM_STATS_ARG
#define MEM_STATS
#endif


#ifdef ML_DECODING
#define OF_LDPC_STAIRCASE_ML_DECODING
#endif


/**
 * Define IL_SUPPORT in debug mode if you want to have the possibility to
 * produce H/G matrix images, e.g. to include in a report on new LDPC code
 * evaluation.
 * More precisely, we are relying on the DevIL library (http://openil.sourceforge.net/).
 * Please install it on your machine before compiling the OpenFEC library
 * if needed.
 */
//#define IL_SUPPORT


/**
 * Default maximum number of source and encoding symbols for this codec.
 * This value depends in particular on the kind of decoder used. To this
 * limit, codec implementation details might add other limits (e.g. if
 * the ESI values are stored in UINT16 instead of UINT32...).
 *
 * Hints:
 * 	If ML decoding is enabled and used, then limit yourself to a value
 * 	that is not too high, since decoding might finish with a Gaussian
 * 	elimination on the simplified system.
 * 	In situations where decoding is restricted to IT, the main limit is
 * 	the available memory. It usually means you can set very large values.
 */
#ifndef OF_LDPC_STAIRCASE_MAX_NB_SOURCE_SYMBOLS_DEFAULT
#ifdef ML_DECODING
#define OF_LDPC_STAIRCASE_MAX_NB_SOURCE_SYMBOLS_DEFAULT		50000
#define OF_LDPC_STAIRCASE_MAX_NB_ENCODING_SYMBOLS_DEFAULT	50000
#else
#define OF_LDPC_STAIRCASE_MAX_NB_SOURCE_SYMBOLS_DEFAULT		100000
#define OF_LDPC_STAIRCASE_MAX_NB_ENCODING_SYMBOLS_DEFAULT	100000
#endif
#endif
