/* $Id: of_reed-solomon_gf_2_8_api.c 186 2014-07-16 07:17:53Z roca $ */
/*
 * OpenFEC.org AL-FEC Library.
 * (c) Copyright 2009 - 2011 INRIA - All rights reserved
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

#include "of_reed-solomon_gf_2_8_includes.h"

#ifdef OF_USE_REED_SOLOMON_CODEC


bool	of_rs_is_source_symbol	(of_rs_cb_t*	ofcb,
				 UINT32		new_symbol_esi)
{
	if (new_symbol_esi < ofcb->nb_source_symbols)
		return true;
	else
		return false;
}


bool	of_rs_is_repair_symbol	(of_rs_cb_t*	ofcb,
				 UINT32		new_symbol_esi)
{
	if (new_symbol_esi < ofcb->nb_source_symbols)
		return false;
	else
		return true;
}


of_status_t of_rs_create_codec_instance (of_rs_cb_t**	of_cb)
{
	of_codec_type_t		codec_type;	/* temporary value */
	of_rs_cb_t		*cb;

	OF_ENTER_FUNCTION
	cb = (of_rs_cb_t*) of_realloc (*of_cb, sizeof (of_rs_cb_t));
	*of_cb = cb;
	/* realloc does not initialize the additional buffer space, so do that manually,
	 * then re-initialize a few parameters */
	codec_type			= cb->codec_type;
	memset(cb, 0, sizeof(*cb));
	cb->codec_type 			= codec_type;
	cb->codec_id			= OF_CODEC_REED_SOLOMON_GF_2_8_STABLE;
	cb->max_nb_source_symbols	= OF_REED_SOLOMON_MAX_NB_SOURCE_SYMBOLS_DEFAULT;	/* init it immediately... */
	cb->max_nb_encoding_symbols	= OF_REED_SOLOMON_MAX_NB_ENCODING_SYMBOLS_DEFAULT;	/* init it immediately... */
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;
}


of_status_t	of_rs_release_codec_instance (of_rs_cb_t*	ofcb)
{
	OF_ENTER_FUNCTION
	UINT32 i;
	if (ofcb->rs_cb != NULL)
	{
		of_rs_free (ofcb->rs_cb);
		ofcb->rs_cb = NULL;
	}
#ifdef OF_USE_DECODER
	if (ofcb->available_symbols_tab != NULL)
	{
		of_free(ofcb->available_symbols_tab);
		ofcb->available_symbols_tab = NULL;
	}
#endif  /* OF_USE_DECODER */
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;
}


of_status_t	of_rs_set_fec_parameters (of_rs_cb_t*		ofcb,
					  of_rs_parameters_t*	params)
{
	OF_ENTER_FUNCTION
	if ((ofcb->nb_source_symbols = params->nb_source_symbols) > ofcb->max_nb_source_symbols) {
		OF_PRINT_ERROR(("of_rs_set_fec_parameters: ERROR, invalid nb_source_symbols parameter (got %d, maximum is %d)",
				ofcb->nb_source_symbols, ofcb->max_nb_source_symbols));
		goto error;
	}
	ofcb->nb_source_symbols = params->nb_source_symbols;
	ofcb->nb_repair_symbols = params->nb_repair_symbols;
	ofcb->encoding_symbol_length = params->encoding_symbol_length;
	ofcb->nb_encoding_symbols = ofcb->nb_source_symbols + ofcb->nb_repair_symbols;
#ifdef OF_USE_DECODER
	ofcb->available_symbols_tab = (void**) of_calloc (ofcb->nb_encoding_symbols, sizeof (void*));
	ofcb->nb_available_symbols = 0;
	ofcb->nb_available_source_symbols = 0;
#endif  /* OF_USE_DECODER */
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;

error:
	OF_EXIT_FUNCTION
	return OF_STATUS_FATAL_ERROR;
}


of_status_t	of_rs_set_callback_functions (of_rs_cb_t*		ofcb,
				       void* (*decoded_source_symbol_callback) (void	*context,
						       UINT32	size,	/* size of decoded source symbol */
						       UINT32	esi),	/* encoding symbol ID in {0..k-1} */
				       void* (*decoded_repair_symbol_callback) (void	*context,
						       UINT32	size,	/* size of decoded repair symbol */
						       UINT32	esi),	/* encoding symbol ID in {0..k-1} */
				       void*	context_4_callback)
{
	ofcb->decoded_source_symbol_callback	=  decoded_source_symbol_callback;
	ofcb->decoded_repair_symbol_callback	=  decoded_repair_symbol_callback;
	ofcb->context_4_callback		=  context_4_callback;
	if (ofcb->decoded_repair_symbol_callback != NULL)
	{
		OF_PRINT_ERROR(("of_rs_set_callback_functions: Warning, the decoded repair symbol callback is never called with Reed-Solomon codes, since those repair symbols are never decoded\n"))
	}
	return OF_STATUS_OK;
}


#ifdef OF_USE_ENCODER
of_status_t	of_rs_build_repair_symbol (of_rs_cb_t*		ofcb,
					   void*		encoding_symbols_tab[],
					   UINT32		esi_of_symbol_to_build)
{
	OF_ENTER_FUNCTION
	if (esi_of_symbol_to_build < ofcb->nb_source_symbols || esi_of_symbol_to_build >= ofcb->nb_encoding_symbols)
	{
		OF_PRINT_ERROR(("of_rs_build_repair_symbol: Error, bad esi of encoding symbol (%d)",
				esi_of_symbol_to_build))
		goto error;
	}
	if (encoding_symbols_tab[esi_of_symbol_to_build] == NULL)
	{
		if ((encoding_symbols_tab[esi_of_symbol_to_build] = of_calloc (1, ofcb->encoding_symbol_length)) == NULL)
		{
			OF_PRINT_ERROR(("of_rs_build_repair_symbol: Error, no memory\n"))
			goto error;
		}
	}
	if (ofcb->rs_cb == NULL)
	{
		/* this is the first time we do an encoding for this codec instance, so initialize
		 * the Reed-Solomon internal codec */
		ofcb->rs_cb = of_rs_new (ofcb->nb_source_symbols, ofcb->nb_encoding_symbols);
		if (ofcb->rs_cb == NULL)
		{
		  OF_PRINT_ERROR(("of_rs_build_repair_symbol: Error, of_rs_new failed"))
		  goto error;
		}
	}
	if (of_rs_encode(ofcb->rs_cb,
			 encoding_symbols_tab,
			 encoding_symbols_tab[esi_of_symbol_to_build],
			 esi_of_symbol_to_build,
			 ofcb->encoding_symbol_length) != OF_STATUS_OK)
	{
		  OF_PRINT_ERROR(("of_rs_build_repair_symbol: Error, of_rs_encode failed"))
		  goto error;
	}
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;

error:
	OF_EXIT_FUNCTION
	return OF_STATUS_ERROR;
}
#endif //OF_USE_ENCODER


#ifdef OF_USE_DECODER
of_status_t of_rs_decode_with_new_symbol (of_rs_cb_t*	ofcb,
					  void*		new_symbol,
					  UINT32	new_symbol_esi)
{
	OF_ENTER_FUNCTION
	if (ofcb->decoding_finished)
	{
		OF_TRACE_LVL(2, ("of_rs_decode_with_new_symbol: decoding already done\n"));
		return OF_STATUS_OK;
	}
	if (ofcb->available_symbols_tab[new_symbol_esi] != NULL)
	{
		/* duplicated symbol, ignore */
		OF_TRACE_LVL(2, ("of_rs_decode_with_new_symbol: symbol (esi=%d) duplicated\n", new_symbol_esi));
		goto end;
	}
	ofcb->available_symbols_tab[new_symbol_esi] = new_symbol;
	ofcb->nb_available_symbols++;
	if (new_symbol_esi < ofcb->nb_source_symbols)
	{
		/* remember a new source symbol is available */
		ofcb->nb_available_source_symbols++;
	}

	if (ofcb->nb_available_source_symbols == ofcb->nb_source_symbols)
	{
		/* we received all the k source symbols, so it's finished */
		ofcb->decoding_finished = true;
		OF_TRACE_LVL(2, ("of_rs_decode_with_new_symbol: done, all source symbols have been received\n"));
		OF_EXIT_FUNCTION
		return OF_STATUS_OK;
	}
	if (ofcb->nb_available_symbols >= ofcb->nb_source_symbols)
	{
		/* we received a sufficient number of symbols, so let's decode */
		if (of_rs_finish_decoding(ofcb) != OF_STATUS_OK)
		{
			OF_PRINT_ERROR(("of_rs_decode_with_new_symbol: Error, of_rs_decode failure\n"))
			goto error;
		}
		ASSERT(ofcb->decoding_finished == true);
		OF_TRACE_LVL(2, ("of_rs_decode_with_new_symbol: done, decoding successful\n"));
		OF_EXIT_FUNCTION
		return OF_STATUS_OK;
	}
end:
	OF_TRACE_LVL(2, ("of_rs_decode_with_new_symbol: okay, but not yet finished\n"));
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;

error:
	OF_EXIT_FUNCTION
	return OF_STATUS_ERROR;
}


of_status_t	of_rs_set_available_symbols    (of_rs_cb_t*	ofcb,
						void* const	encoding_symbols_tab[])
{
	UINT32	i;

	OF_ENTER_FUNCTION
	ofcb->nb_available_symbols = 0;
	ofcb->nb_available_source_symbols = 0;
	for (i = 0; i < ofcb->nb_encoding_symbols; i++)
	{
		if ((ofcb->available_symbols_tab[i] = encoding_symbols_tab[i]) == NULL)
		{
			continue;	
		}
		if (i < ofcb->nb_source_symbols)
		{
			ofcb->nb_available_source_symbols++;
		}
		ofcb->nb_available_symbols++;
	}
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;
}


of_status_t	of_rs_finish_decoding (of_rs_cb_t*	ofcb)
{
	UINT32 		k;
	UINT32 		n;
	char		*tmp_buf[GF_SIZE];	/* copy available source/repair symbol buffers here... */
	int		tmp_esi[GF_SIZE];	/* ...and their esi here. In fact we only need k entries
						 * in these tables, but in order to avoid using malloc (time
						 * consumming), we use an automatic table of maximum size for
						 * both tmp_buf[] and tmp_esi[]. */
	INT32		tmp_idx;		/* index in tmp_buf[] and tmp_esi[] tabs */
	char		*large_buf = NULL;	/* single large buffer where to copy all source/repair symbols */
	UINT32		off;			/* offset, in unit of characters, in large_buf */
	void		**ass_buf;		/* tmp pointer to the current source symbol entry in
						 * available_symbols_tab[] */
	UINT32		ass_esi;		/* corresponding available source symbol ESI */
	void		**ars_buf;		/* tmp pointer to the current repair symbol entry in
						 * available_symbols_tab[] */
	UINT32		ars_esi;		/* corresponding available repair symbol ESI */

	OF_ENTER_FUNCTION
	if (ofcb->decoding_finished)
	{
		return OF_STATUS_OK;
	}
	k = ofcb->nb_source_symbols;
	n = ofcb->nb_encoding_symbols;
	if (ofcb->nb_available_symbols < k)
	{
		OF_PRINT_ERROR(("of_rs_finish_decoding: Error, nb received symbols < nb source symbols\n"))
		OF_EXIT_FUNCTION
		return OF_STATUS_FAILURE;
	}
	if (ofcb->nb_available_source_symbols == k)
	{
		/* we received all the k source symbols, so it's finished */
		ofcb->decoding_finished = true;
		OF_EXIT_FUNCTION
		return OF_STATUS_OK;
	}
	/*
	 * Copy available source and repair symbols in a single large buffer first.
	 * NB: this is required by the current FEC codec which modifies
	 * the tmp_buf buffers!!!
	 */
	large_buf = (char *) of_malloc(k * ofcb->encoding_symbol_length);
	if (large_buf == NULL)
	{
		goto no_mem;
	}
	/* Then remember the location of each symbol buffer */
	for (tmp_idx = 0, off = 0; tmp_idx < k; tmp_idx++, off += ofcb->encoding_symbol_length) {
		tmp_buf[tmp_idx] = large_buf + off;
	}
	tmp_idx	= 0;			/* index in tmp_buf and tmp_esi tables */
	/*
	 * Copy all the available source symbols (it's essential for decoding speed purposes) and
	 * a sufficient number of repair symbols to the tmp_buf array. Copy data as well in the
	 * large_buf buffer.
	 * Because of of_rs_decode internal details, we put source symbols at their right location
	 * and fill in the gaps (i.e. erased source symbols) with repair symbols.
	 */
	ass_esi = 0;
	ars_esi = k;
	ass_buf = ofcb->available_symbols_tab;
	ars_buf = ofcb->available_symbols_tab + k;
	for (tmp_idx = 0; tmp_idx < k; tmp_idx++)
	{
		if (*ass_buf == NULL)
		{
			/* this source symbol is not available, replace it with a repair */
			while (*ars_buf == NULL)
			{
				ars_esi++;
				ars_buf++;
			}
			OF_TRACE_LVL(2, ("of_rs_finish_decoding: copy repair with esi=%d in tmp_buf[%d]\n",
					ars_esi, tmp_idx))
			memcpy(tmp_buf[tmp_idx], *ars_buf, ofcb->encoding_symbol_length);
			tmp_esi[tmp_idx] = ars_esi;
			ars_esi++;
			ars_buf++;
		}
		else
		{
			OF_TRACE_LVL(2, ("of_rs_finish_decoding: copy source with esi=%d in tmp_buf[%d]\n",
					ars_esi, tmp_idx))
			memcpy(tmp_buf[tmp_idx], *ass_buf, ofcb->encoding_symbol_length);
			tmp_esi[tmp_idx] = ass_esi;
		}
		ass_esi++;
		ass_buf++;
	}
#if 0
	for (tmp_idx = 0; tmp_idx < k; tmp_idx++)
	{
		OF_TRACE_LVL(2, ("Before of_rs_decode: esi=%d, k=%d, tmp_idx=%d\n", tmp_esi[tmp_idx], k, tmp_idx))
	}
#endif
	/*
	 * Let's decode now.
	 * Create a context first, decode, then release this context.
	 */
	ofcb->rs_cb = of_rs_new (ofcb->nb_source_symbols, ofcb->nb_encoding_symbols);
	if (of_rs_decode (ofcb->rs_cb, (void**)tmp_buf, (int*)tmp_esi, ofcb->encoding_symbol_length) != OF_STATUS_OK)
	{
		OF_PRINT_ERROR(("of_rs_finish_decoding: Error, of_rs_decode failure\n"))
		goto error;
	}
	of_rs_free (ofcb->rs_cb);
	ofcb->rs_cb = NULL;
	ofcb->decoding_finished = true;
#if 0
	for (tmp_idx = 0; tmp_idx < k; tmp_idx++)
	{
		OF_TRACE_LVL(2, ("After of_rs_decode: esi=%d, k=%d, tmp_idx=%d\n", tmp_esi[tmp_idx], k, tmp_idx))
	}
#endif
	/*
	 * finally update the source_symbols_tab table with the decoded source symbols.
	 */
	for (tmp_idx = 0; tmp_idx < k; tmp_idx++)
	{
		ASSERT(tmp_idx < k);
		ass_buf = &(ofcb->available_symbols_tab[tmp_idx]);
		if (*ass_buf != NULL)
		{
			/* nothing to do, this source symbol has already been received. */
			continue;
		}
		/*
		 * This is a new, decoded source symbol.
		 * First copy it into a permanent buffer.
		 * Call either the associated callback or allocate memory, and then
		 * copy the symbol content in it.
		 */
		if (ofcb->decoded_source_symbol_callback != NULL)
		{
			*ass_buf = ofcb->decoded_source_symbol_callback (ofcb->context_4_callback,
									ofcb->encoding_symbol_length, tmp_idx);
		}
		else
		{
			*ass_buf = (void *) of_malloc (ofcb->encoding_symbol_length);
		}
		if (*ass_buf == NULL)
		{
			goto no_mem;
		}
		memcpy(*ass_buf, tmp_buf[tmp_idx], ofcb->encoding_symbol_length);
		OF_TRACE_LVL(2, ("of_rs_finish_decoding: decoded source symbol esi=%d from tmp_buf[%d]\n",
				tmp_idx, tmp_idx))
	}
	of_free(large_buf);
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;
no_mem:
	OF_PRINT_ERROR(("of_rs_finish_decoding: out of memory.\n"))

error:
	OF_EXIT_FUNCTION
	return OF_STATUS_ERROR;
}


bool	of_rs_is_decoding_complete (of_rs_cb_t* ofcb)
{
	OF_ENTER_FUNCTION
	OF_EXIT_FUNCTION
	return ofcb->decoding_finished;
}


of_status_t	of_rs_get_source_symbols_tab   (of_rs_cb_t*	ofcb,
						void*		source_symbols_tab[])
{
	OF_ENTER_FUNCTION
	if (of_rs_is_decoding_complete(ofcb) == false)
	{
		OF_PRINT_ERROR(("of_rs_get_source_symbols_tab: Error, decoding not complete.\n"))
		OF_EXIT_FUNCTION
		return OF_STATUS_ERROR;
	}
#if 0
	UINT32	i;
	for (i = 0; i < ofcb->nb_source_symbols; i++)
	{
		if (source_symbols_tab[i] == NULL)
		{
			source_symbols_tab[i] = ofcb->available_symbols_tab[i];
		}
	}
#else
	memcpy(source_symbols_tab, ofcb->available_symbols_tab, ofcb->nb_source_symbols * sizeof(void*));
#endif
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;
}
	

#endif  //OF_USE_DECODER

of_status_t	of_rs_set_control_parameter    (of_rs_cb_t*	ofcb,
						UINT32		type,
						void*		value,
						UINT32		length)
{
	OF_PRINT_ERROR(("of_rs_set_control_parameter: ERROR, not implemented...\n"))
	return OF_STATUS_ERROR;
}


of_status_t	of_rs_get_control_parameter    (of_rs_cb_t*	ofcb,
						UINT32		type,
						void*		value,
						UINT32		length)
{
	OF_ENTER_FUNCTION
	switch (type) {
	case OF_CTRL_GET_MAX_K:
		if (value == NULL || length != sizeof(UINT32)) {
			OF_PRINT_ERROR(("%s: OF_CTRL_GET_MAX_K ERROR: null value or bad length (got %d, expected %zu)\n",
				__FUNCTION__, length, sizeof(UINT32)))
			goto error;
		}
		*(UINT32*)value = ofcb->max_nb_source_symbols;
		OF_TRACE_LVL(1, ("%s: OF_CTRL_GET_MAX_K (%d)\n", __FUNCTION__, *(UINT32*)value))
		break;

	case OF_CTRL_GET_MAX_N:
		if (value == NULL || length != sizeof(UINT32)) {
			OF_PRINT_ERROR(("%s: OF_CTRL_GET_MAX_N ERROR: null value or bad length (got %d, expected %zu)\n",
				__FUNCTION__, length, sizeof(UINT32)))
			goto error;
		}
		*(UINT32*)value = ofcb->max_nb_encoding_symbols;
		OF_TRACE_LVL(1, ("%s: OF_CTRL_GET_MAX_N (%d)\n", __FUNCTION__, *(UINT32*)value))
		break;

	default:
		OF_PRINT_ERROR(("%s: unknown type (%d)\n", __FUNCTION__, type))
		goto error;
	}
	OF_EXIT_FUNCTION
	return OF_STATUS_OK;

error:
	OF_EXIT_FUNCTION
	return OF_STATUS_ERROR;
}

#endif //#ifdef OF_USE_REED_SOLOMON_CODEC
