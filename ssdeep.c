/**
 *
 * php_ssdeep
 *
 * http://treffynnon.github.com/php_ssdeep/
 *
 * A PHP extension to expose ssdeep functionality for fuzzy
 * hashing and comparing.
 *
 * Version 1.0.4
 *
 * BSD Licensed.
 *
 * Copyright (c) 2014, Simon Holywell
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "SAPI.h"
#include "php_ssdeep.h"
#include <fuzzy.h>

/* True global resources - no need for thread safety here */
ZEND_BEGIN_ARG_INFO_EX(arginfo_ssdeep_fuzzy_hash, 0, 0, 1)
    ZEND_ARG_INFO(0, to_hash)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ssdeep_fuzzy_hash_filename, 0, 0, 1)
    ZEND_ARG_INFO(0, file_name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ssdeep_fuzzy_compare, 0, 0, 2)
    ZEND_ARG_INFO(0, signature1)
    ZEND_ARG_INFO(0, signature2)
ZEND_END_ARG_INFO()

/* {{{ ssdeep_functions[]
 */
const zend_function_entry ssdeep_functions[] = {
    PHP_FE(ssdeep_fuzzy_hash, arginfo_ssdeep_fuzzy_hash)
    PHP_FE(ssdeep_fuzzy_hash_filename, arginfo_ssdeep_fuzzy_hash_filename)
    PHP_FE(ssdeep_fuzzy_compare, arginfo_ssdeep_fuzzy_compare) {
        NULL, NULL, NULL} /* Must be the last line in ssdeep_functions[] */
};
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ssdeep) {
    php_info_print_table_start();
    php_info_print_table_row(2, PHP_SSDEEP_EXTNAME " Module", "enabled");
    php_info_print_table_row(2, "version", PHP_SSDEEP_VERSION);
    if (sapi_module.phpinfo_as_text) {
        /* No HTML for you */
        php_info_print_table_row(2, "By",
                "Simon Holywell\nhttp://www.simonholywell.com");
    } else {
        /* HTMLified version */
        php_printf("<tr>"
                "<td class=\"v\">By</td>"
                "<td class=\"v\">"
                "<a href=\"http://www.simonholywell.com\""
                " alt=\"Simon Holywell\">"
                "Simon Holywell"
                "</a></td></tr>");
    }
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto string ssdeep_fuzzy_hash(string to_hash)
 */
PHP_FUNCTION(ssdeep_fuzzy_hash) {
    char *hash = (char *) emalloc(FUZZY_MAX_RESULT);
    char *to_hash;
    int to_hash_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &to_hash, &to_hash_len) == FAILURE) {
        RETURN_NULL();
    }

    if (0 != fuzzy_hash_buf((unsigned char *) to_hash, to_hash_len, hash)) {
        RETURN_FALSE;
    } else {
        RETURN_STRING(hash, 0);
    }
}
/* }}} */

/* {{{ proto string ssdeep_fuzzy_hash_filename(string file_name)
 */
PHP_FUNCTION(ssdeep_fuzzy_hash_filename) {
    char *hash = (char *) emalloc(FUZZY_MAX_RESULT);
    char *file_name;
    int file_name_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file_name, &file_name_len) == FAILURE) {
        RETURN_NULL();
    }

    if (0 != fuzzy_hash_filename(file_name, hash)) {
        RETURN_FALSE;
    } else {
        RETURN_STRING(hash, 0);
    }
}
/* }}} */

/* {{{ proto long ssdeep_fuzzy_compare(string signature1, string signature2)
 */
PHP_FUNCTION(ssdeep_fuzzy_compare) {
    char *signature1 = NULL;
    int signature1_len;
    char *signature2 = NULL;
    int signature2_len;
    int match;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &signature1, &signature1_len, &signature2, &signature2_len) == FAILURE) {
        RETURN_NULL();
    }
    match = fuzzy_compare(signature1, signature2);
	
	if(match < 0 || match > 100) {
		RETURN_FALSE;
	} else {
		RETURN_LONG(match);
	}
}
/* }}} */

/* {{{ ssdeep_module_entry
 */
zend_module_entry ssdeep_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_SSDEEP_EXTNAME,
    ssdeep_functions,
    NULL /* PHP_MINIT(ssdeep) */,
    NULL /* PHP_MSHUTDOWN(ssdeep) */,
    NULL /* PHP_RINIT(ssdeep) */, /* Replace with NULL if there's nothing to do at request start */
    NULL /* PHP_RSHUTDOWN(ssdeep)*/, /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(ssdeep),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_SSDEEP_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SSDEEP
ZEND_GET_MODULE(ssdeep)
#endif
