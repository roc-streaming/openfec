/* $Id: of_openfec_profile.h 207 2014-12-10 19:47:50Z roca $ */
/*
 * OpenFEC.org AL-FEC Library.
 * (c) Copyright 2009 - 2012 INRIA - All rights reserved
 * Contact: vincent.roca@inria.fr
 *
 * This software is governed by the CeCILL-C license under French law and
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

#ifndef OF_OPENFEC_PROFILE_H
#define OF_OPENFEC_PROFILE_H

#include "of_build_config.h"

#ifdef OF_USE_REED_SOLOMON_CODEC
#include "../lib_stable/reed-solomon_gf_2_8/of_codec_profile.h"
#endif

#ifdef OF_USE_REED_SOLOMON_2_M_CODEC
#include "../lib_stable/reed-solomon_gf_2_m/of_codec_profile.h"
#endif

#ifdef OF_USE_LDPC_STAIRCASE_CODEC
#include "../lib_stable/ldpc_staircase/of_codec_profile.h"
#endif

#ifdef OF_USE_2D_PARITY_MATRIX_CODEC
#include "../lib_stable/2d_parity_matrix/of_codec_profile.h"
#endif

#ifdef OF_USE_LDPC_FROM_FILE_CODEC
#include "../lib_advanced/ldpc_from_file/of_codec_profile.h"
#endif

#endif // OF_OPENFEC_PROFILE_H
