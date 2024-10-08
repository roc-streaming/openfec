# list of dedicated binary tests
add_executable(test_create_instance create_instance_test.c)
target_link_libraries(test_create_instance openfec m)
add_test("create_instance" ${EXECUTABLE_OUTPUT_PATH}/test_create_instance)
set_tests_properties ("create_instance"
	PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR;FAILURE")

add_executable(test_encoder_instance encoder_instance_test.c)
target_link_libraries(test_encoder_instance openfec m)
add_test("encoder_instance" ${EXECUTABLE_OUTPUT_PATH}/test_encoder_instance)
set_tests_properties ("encoder_instance"
	PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR;FAILURE")

add_executable(test_code_params code_params_test.c)
target_link_libraries(test_code_params openfec m)
add_test("code_params" ${EXECUTABLE_OUTPUT_PATH}/test_code_params)
set_tests_properties ("code_params"
	PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR;FAILURE")


# definition of the do_test macro used below
macro (do_test name)
    add_test(Test.${name} ${EPERFTOOL_BIN} ${ARGN})
    set_tests_properties (Test.${name}
        PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR;FAILURE")
endmacro(do_test)


# list of automatic tests using eperftool. Add your own tests here...

#
# PART 1: LDPC-Staircase tests
#
if(OF_USE_LDPC_STAIRCASE_CODEC)

# Robustness in front of many transmission types
#
do_test(LDPC-SC-ADV.cr2.3.tx0 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500)
do_test(LDPC-SC-ADV.cr1.2.tx1 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=1)
do_test(LDPC-SC-ADV.cr1.2.tx2 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=2)
do_test(LDPC-SC.cr1.2.tx3   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=1090 -tx_type=3)
do_test(LDPC-SC.cr2.3.tx4   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=4)
do_test(LDPC-SC.cr2.3.tx5   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=5)
do_test(LDPC-SC.cr2.3.tx6   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=6)
do_test(LDPC-SC.cr2.3.tx7   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=7)
do_test(LDPC-SC.cr2.3.loss1 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -loss=2:30)
do_test(LDPC-SC.cr2.3.loss2 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -loss=3:480)
do_test(LDPC-SC.cr2.3.loss3 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500 -loss=1)
do_test(LDPC-SC.cr1.2.loss4 	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=1000 -loss=4)
do_test(LDPC-SC.cr3.4.tx4   	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=4)
do_test(LDPC-SC.cr3.4.tx5   	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=5)
do_test(LDPC-SC.cr3.4.tx6   	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=6)
do_test(LDPC-SC.cr3.4.tx7   	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=7)
do_test(LDPC-SC.cr3.4.loss1 	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -loss=2:24)
do_test(LDPC-SC.cr3.4.loss2 	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -loss=3:480)
do_test(LDPC-SC.cr3.4.loss3 	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=500 -loss=1)
do_test(LDPC-SC.cr3.4.loss4 	 -codec=3 -seed=1 -tot_src=1500 -tot_rep=1000 -loss=4)

# IT decoding tests
#
do_test(LDPC-SC.cr2.3.small.IT   	 -codec=3 -seed=1 -tot_src=100 -tot_rep=50)
do_test(LDPC-SC.cr1.2.small.IT   	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100)
do_test(LDPC-SC.cr1.3.small.IT   	 -codec=3 -seed=1 -tot_src=100 -tot_rep=200)
do_test(LDPC-SC.cr1.4.small.IT   	 -codec=3 -seed=1 -tot_src=100 -tot_rep=300)
do_test(LDPC-SC.cr1.5.small.IT   	 -codec=3 -seed=1 -tot_src=100 -tot_rep=400)

do_test(LDPC-SC.cr3.4.med.IT   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=500)
do_test(LDPC-SC.cr1.2.med.IT   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=1000)
do_test(LDPC-SC.cr1.3.med.IT   	 -codec=3 -seed=1 -tot_src=1000 -tot_rep=2000)

do_test(LDPC-SC.src1.IT  	 -codec=3 -seed=1 -tot_src=1  -tot_rep=23)
do_test(LDPC-SC.src2.IT  	 -codec=3 -seed=1 -tot_src=2  -tot_rep=23)
do_test(LDPC-SC.src3.IT  	 -codec=3 -seed=1 -tot_src=3  -tot_rep=23)
do_test(LDPC-SC.src4.IT  	 -codec=3 -seed=1 -tot_src=4  -tot_rep=23)
do_test(LDPC-SC.src5.IT  	 -codec=3 -seed=1 -tot_src=5  -tot_rep=23)
do_test(LDPC-SC.src6.IT  	 -codec=3 -seed=1 -tot_src=6  -tot_rep=23)
do_test(LDPC-SC.src7.IT  	 -codec=3 -seed=1 -tot_src=7  -tot_rep=23)
do_test(LDPC-SC.src8.IT  	 -codec=3 -seed=1 -tot_src=8  -tot_rep=23)
do_test(LDPC-SC.src9.IT  	 -codec=3 -seed=1 -tot_src=9  -tot_rep=23)
do_test(LDPC-SC.src10.IT 	 -codec=3 -seed=1 -tot_src=10 -tot_rep=23)
do_test(LDPC-SC.src11.IT 	 -codec=3 -seed=1 -tot_src=11 -tot_rep=23)
do_test(LDPC-SC.src12.IT 	 -codec=3 -seed=1 -tot_src=12 -tot_rep=23)
do_test(LDPC-SC.src13.IT 	 -codec=3 -seed=1 -tot_src=13 -tot_rep=23)
do_test(LDPC-SC.src14.IT 	 -codec=3 -seed=1 -tot_src=14 -tot_rep=23)
do_test(LDPC-SC.src15.IT 	 -codec=3 -seed=1 -tot_src=15 -tot_rep=23)
do_test(LDPC-SC.src16.IT 	 -codec=3 -seed=1 -tot_src=16 -tot_rep=23)
do_test(LDPC-SC.src17.IT 	 -codec=3 -seed=1 -tot_src=17 -tot_rep=23)
do_test(LDPC-SC.src18.IT 	 -codec=3 -seed=1 -tot_src=18 -tot_rep=23)
do_test(LDPC-SC.src19.IT 	 -codec=3 -seed=1 -tot_src=19 -tot_rep=23)
do_test(LDPC-SC.src20.IT 	 -codec=3 -seed=1 -tot_src=20 -tot_rep=23)
do_test(LDPC-SC.src21.IT 	 -codec=3 -seed=1 -tot_src=21 -tot_rep=23)
do_test(LDPC-SC.src22.IT 	 -codec=3 -seed=1 -tot_src=22 -tot_rep=23)
do_test(LDPC-SC.src23.IT 	 -codec=3 -seed=1 -tot_src=23 -tot_rep=23)
do_test(LDPC-SC.src24.IT 	 -codec=3 -seed=1 -tot_src=24 -tot_rep=23)
do_test(LDPC-SC.src25.IT 	 -codec=3 -seed=1 -tot_src=25 -tot_rep=23)
do_test(LDPC-SC.src26.IT 	 -codec=3 -seed=1 -tot_src=26 -tot_rep=23)
do_test(LDPC-SC.src27.IT 	 -codec=3 -seed=1 -tot_src=27 -tot_rep=23)
do_test(LDPC-SC.src28.IT 	 -codec=3 -seed=1 -tot_src=28 -tot_rep=23)
do_test(LDPC-SC.src29.IT 	 -codec=3 -seed=1 -tot_src=29 -tot_rep=23)
do_test(LDPC-SC.src30.IT 	 -codec=3 -seed=1 -tot_src=30 -tot_rep=23)
do_test(LDPC-SC.src31.IT 	 -codec=3 -seed=1 -tot_src=31 -tot_rep=23)
do_test(LDPC-SC.src32.IT 	 -codec=3 -seed=1 -tot_src=32 -tot_rep=23)
do_test(LDPC-SC.src33.IT 	 -codec=3 -seed=1 -tot_src=33 -tot_rep=23)
do_test(LDPC-SC.src34.IT 	 -codec=3 -seed=1 -tot_src=34 -tot_rep=23)
do_test(LDPC-SC.src35.IT 	 -codec=3 -seed=1 -tot_src=35 -tot_rep=23)
do_test(LDPC-SC.src36.IT 	 -codec=3 -seed=1 -tot_src=36 -tot_rep=23)
do_test(LDPC-SC.src37.IT 	 -codec=3 -seed=1 -tot_src=37 -tot_rep=23)
do_test(LDPC-SC.src38.IT 	 -codec=3 -seed=1 -tot_src=38 -tot_rep=23)
do_test(LDPC-SC.src39.IT 	 -codec=3 -seed=1 -tot_src=39 -tot_rep=23)
do_test(LDPC-SC.src40.IT 	 -codec=3 -seed=1 -tot_src=40 -tot_rep=23)

# ML decoding tests
# we set the -find_min.MLerhead flag to force ML decoding
#
do_test(LDPC-SC.cr2.3.small.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=100 -tot_rep=50)
do_test(LDPC-SC.cr1.2.small.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=100 -tot_rep=100)
do_test(LDPC-SC.cr1.3.small.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=100 -tot_rep=200)
do_test(LDPC-SC.cr1.4.small.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=100 -tot_rep=300)
do_test(LDPC-SC.cr1.5.small.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=100 -tot_rep=400)

do_test(LDPC-SC.cr3.4.med.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=1000 -tot_rep=500)
do_test(LDPC-SC.cr1.2.med.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=1000 -tot_rep=1000)
do_test(LDPC-SC.cr1.3.med.ML   	 -codec=3 -seed=1 -find_min_overhead -tot_src=1000 -tot_rep=2000)

do_test(LDPC-SC.src1.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=1  -tot_rep=23)
do_test(LDPC-SC.src2.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=2  -tot_rep=23)
do_test(LDPC-SC.src3.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=3  -tot_rep=23)
do_test(LDPC-SC.src4.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=4  -tot_rep=23)
do_test(LDPC-SC.src5.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=5  -tot_rep=23)
do_test(LDPC-SC.src6.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=6  -tot_rep=23)
do_test(LDPC-SC.src7.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=7  -tot_rep=23)
do_test(LDPC-SC.src8.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=8  -tot_rep=23)
do_test(LDPC-SC.src9.ML  	 -codec=3 -seed=1 -find_min_overhead -tot_src=9  -tot_rep=23)
do_test(LDPC-SC.src10.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=10 -tot_rep=23)
do_test(LDPC-SC.src11.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=11 -tot_rep=23)
do_test(LDPC-SC.src12.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=12 -tot_rep=23)
do_test(LDPC-SC.src13.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=13 -tot_rep=23)
do_test(LDPC-SC.src14.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=14 -tot_rep=23)
do_test(LDPC-SC.src15.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=15 -tot_rep=23)
do_test(LDPC-SC.src16.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=16 -tot_rep=23)
do_test(LDPC-SC.src17.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=17 -tot_rep=23)
do_test(LDPC-SC.src18.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=18 -tot_rep=23)
do_test(LDPC-SC.src19.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=19 -tot_rep=23)
do_test(LDPC-SC.src20.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=20 -tot_rep=23)
do_test(LDPC-SC.src21.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=21 -tot_rep=23)
do_test(LDPC-SC.src22.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=22 -tot_rep=23)
do_test(LDPC-SC.src23.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=23 -tot_rep=23)
do_test(LDPC-SC.src24.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=24 -tot_rep=23)
do_test(LDPC-SC.src25.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=25 -tot_rep=23)
do_test(LDPC-SC.src26.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=26 -tot_rep=23)
do_test(LDPC-SC.src27.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=27 -tot_rep=23)
do_test(LDPC-SC.src28.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=28 -tot_rep=23)
do_test(LDPC-SC.src29.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=29 -tot_rep=23)
do_test(LDPC-SC.src30.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=30 -tot_rep=23)
do_test(LDPC-SC.src31.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=31 -tot_rep=23)
do_test(LDPC-SC.src32.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=32 -tot_rep=23)
do_test(LDPC-SC.src33.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=33 -tot_rep=23)
do_test(LDPC-SC.src34.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=34 -tot_rep=23)
do_test(LDPC-SC.src35.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=35 -tot_rep=23)
do_test(LDPC-SC.src36.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=36 -tot_rep=23)
do_test(LDPC-SC.src37.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=37 -tot_rep=23)
do_test(LDPC-SC.src38.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=38 -tot_rep=23)
do_test(LDPC-SC.src39.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=39 -tot_rep=23)
do_test(LDPC-SC.src40.ML 	 -codec=3 -seed=1 -find_min_overhead -tot_src=40 -tot_rep=23)

# Test with big objects and various code rates, using IT decoding
#
do_test(LDPC-SC.cr2.3.big.IT   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=5000)
do_test(LDPC-SC.cr1.2.big.IT   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=10000)
do_test(LDPC-SC.cr1.3.big.IT   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=20000)
#do_test(LDPC-SC.cr1.4.big.IT   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=30000)

# Test with big objects and various code rates, using ML decoding
#
do_test(LDPC-SC.cr2.3.big.ML   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=5000 -find_min_overhead)
#do_test(LDPC-SC.cr1.2.big.ML   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=10000 -find_min_overhead)
#do_test(LDPC-SC.cr1.3.big.ML   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=20000 -find_min_overhead)
#do_test(LDPC-SC.cr1.4.big.ML   	 -codec=3 -seed=1 -tot_src=10000 -tot_rep=30000 -find_min_overhead)

# symbol size tests: the codec must be able to accomodate any symbol size
#
do_test(LDPC-SC.ss1 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=1)
do_test(LDPC-SC.ss2 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=2)
do_test(LDPC-SC.ss3 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=3)
do_test(LDPC-SC.ss4 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=4)
do_test(LDPC-SC.ss5 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=5)
do_test(LDPC-SC.ss6 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=6)
do_test(LDPC-SC.ss7 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=7)
do_test(LDPC-SC.ss8 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=8)
do_test(LDPC-SC.ss9 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=9)
do_test(LDPC-SC.ss10 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=10)
do_test(LDPC-SC.ss11 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=11)
do_test(LDPC-SC.ss12 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=12)
do_test(LDPC-SC.ss13 	 -codec=3 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=13)

#
#
endif(OF_USE_LDPC_STAIRCASE_CODEC)


#
# PART 2: Reed-Solomon over GF(2m), with m=4, tests
#
if(OF_USE_REED_SOLOMON_2_M_CODEC)

do_test(RS_2m_4.src1 		-codec=2 -rs_m=4 -seed=1 -tot_src=1 -tot_rep=23)
do_test(RS_2m_4.src2 		-codec=2 -rs_m=4 -seed=1 -tot_src=2 -tot_rep=23)
do_test(RS_2m_4.src3 		-codec=2 -rs_m=4 -seed=1 -tot_src=3 -tot_rep=23)
do_test(RS_2m_4.src4 		-codec=2 -rs_m=4 -seed=1 -tot_src=4 -tot_rep=23)
do_test(RS_2m_4.src11 		-codec=2 -rs_m=4 -seed=1 -tot_src=11 -tot_rep=23)
do_test(RS_2m_4.src13 		-codec=2 -rs_m=4 -seed=1 -tot_src=13 -tot_rep=23)
do_test(RS_2m_4.src15 		-codec=2 -rs_m=4 -seed=1 -tot_src=15 -tot_rep=23)
do_test(RS_2m_4.src17 		-codec=2 -rs_m=4 -seed=1 -tot_src=17 -tot_rep=23)
do_test(RS_2m_4.src21 		-codec=2 -rs_m=4 -seed=1 -tot_src=21 -tot_rep=23)

do_test(RS_2m_4.cr2.3.tx0 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500)
do_test(RS_2m_4.cr1.2.tx1 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=1)
do_test(RS_2m_4.cr1.2.tx2 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=2)
do_test(RS_2m_4.cr1.2.tx3 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=1090 -tx_type=3)
do_test(RS_2m_4.cr2.3.tx4 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=4)
do_test(RS_2m_4.cr2.3.tx5 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=5)
do_test(RS_2m_4.cr2.3.tx6 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=6)
do_test(RS_2m_4.cr2.3.tx7 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=7)
do_test(RS_2m_4.cr2.3.loss1 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -loss=2:10)		# 10% loss rate only with GF(2^4)
do_test(RS_2m_4.cr2.3.loss2 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -loss=3:100)	# 100 lost packets only with GF(2^4)
do_test(RS_2m_4.cr2.3.loss3 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=500 -loss=1)
do_test(RS_2m_4.cr1.2.loss4 	-codec=2 -rs_m=4 -seed=1 -tot_src=1000 -tot_rep=4000 -loss=4)		# 4000 redundant packets needed with GF(2^4)
do_test(RS_2m_4.cr2.3.big 	-codec=2 -rs_m=4 -seed=1 -tot_src=10000 -tot_rep=5000)
do_test(RS_2m_4.cr3.4.tx4 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=4)
do_test(RS_2m_4.cr3.4.tx5 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=5)
do_test(RS_2m_4.cr3.4.tx6 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=6)
do_test(RS_2m_4.cr3.4.tx7 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=7)
do_test(RS_2m_4.cr3.4.loss1 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=500 -loss=2:5)		# 5% loss rate only with GF(2^4)
do_test(RS_2m_4.cr3.4.loss2 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=500 -loss=3:100)	# 100 lost packets only with GF(2^4)
do_test(RS_2m_4.cr3.4.loss3 	-codec=2 -rs_m=4 -seed=1 -tot_src=1500 -tot_rep=1500 -loss=1)		# 1500 redundant packets needed with GF(2^4)
do_test(RS_2m_4.cr3.4.big 	-codec=2 -rs_m=4 -seed=1 -tot_src=15000 -tot_rep=5000)

do_test(RS_2m_4.ss1 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=1)
do_test(RS_2m_4.ss2 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=2)
do_test(RS_2m_4.ss3 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=3)
do_test(RS_2m_4.ss4 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=4)
do_test(RS_2m_4.ss5 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=5)
do_test(RS_2m_4.ss6 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=6)
do_test(RS_2m_4.ss7 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=7)
do_test(RS_2m_4.ss8 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=8)
do_test(RS_2m_4.ss9	 	-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=9)
do_test(RS_2m_4.ss10 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=10)
do_test(RS_2m_4.ss11 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=11)
do_test(RS_2m_4.ss12 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=12)
do_test(RS_2m_4.ss13 		-codec=2 -rs_m=4 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=13)


#
# PART 3: Reed-Solomon over GF(2m), with m=8, tests
#

do_test(RS_2m_8.src1 		-codec=2 -rs_m=8 -seed=1 -tot_src=1 -tot_rep=23)
do_test(RS_2m_8.src2 		-codec=2 -rs_m=8 -seed=1 -tot_src=2 -tot_rep=23)
do_test(RS_2m_8.src3 		-codec=2 -rs_m=8 -seed=1 -tot_src=3 -tot_rep=23)
do_test(RS_2m_8.src4 		-codec=2 -rs_m=8 -seed=1 -tot_src=4 -tot_rep=23)
do_test(RS_2m_8.src11 		-codec=2 -rs_m=8 -seed=1 -tot_src=11 -tot_rep=23)
do_test(RS_2m_8.src13 		-codec=2 -rs_m=8 -seed=1 -tot_src=13 -tot_rep=23)
do_test(RS_2m_8.src15 		-codec=2 -rs_m=8 -seed=1 -tot_src=15 -tot_rep=23)
do_test(RS_2m_8.src17 		-codec=2 -rs_m=8 -seed=1 -tot_src=17 -tot_rep=23)
do_test(RS_2m_8.src21 		-codec=2 -rs_m=8 -seed=1 -tot_src=21 -tot_rep=23)

do_test(RS_2m_8.cr2.3.tx0 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500)
do_test(RS_2m_8.cr1.2.tx1 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=1)
do_test(RS_2m_8.cr1.2.tx2 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=2)
do_test(RS_2m_8.cr1.2.tx3 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1090 -tx_type=3)
do_test(RS_2m_8.cr2.3.tx4 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=4)
do_test(RS_2m_8.cr2.3.tx5 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=5)
do_test(RS_2m_8.cr2.3.tx6 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=6)
do_test(RS_2m_8.cr2.3.tx7 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=7)
do_test(RS_2m_8.cr2.3.loss1 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -loss=2:20)
do_test(RS_2m_8.cr2.3.loss2 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -loss=3:400)
do_test(RS_2m_8.cr2.3.loss3 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -loss=1)
do_test(RS_2m_8.cr1.2.loss4 	-codec=2 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1000 -loss=4)
do_test(RS_2m_8.cr2.3.big 	-codec=2 -rs_m=8 -seed=1 -tot_src=10000 -tot_rep=5000)
do_test(RS_2m_8.cr3.4.tx4 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=4)
do_test(RS_2m_8.cr3.4.tx5 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=5)
do_test(RS_2m_8.cr3.4.tx6 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=6)
do_test(RS_2m_8.cr3.4.tx7 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=7)
do_test(RS_2m_8.cr3.4.loss1 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -loss=2:20)
do_test(RS_2m_8.cr3.4.loss2 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -loss=3:380)
do_test(RS_2m_8.cr3.4.loss3 	-codec=2 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -loss=1)
do_test(RS_2m_8.cr3.4.big 	-codec=2 -rs_m=8 -seed=1 -tot_src=15000 -tot_rep=5000)

do_test(RS_2m_8.ss1 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=1)
do_test(RS_2m_8.ss2 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=2)
do_test(RS_2m_8.ss3 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=3)
do_test(RS_2m_8.ss4 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=4)
do_test(RS_2m_8.ss5 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=5)
do_test(RS_2m_8.ss6 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=6)
do_test(RS_2m_8.ss7 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=7)
do_test(RS_2m_8.ss8 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=8)
do_test(RS_2m_8.ss9	 	-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=9)
do_test(RS_2m_8.ss10 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=10)
do_test(RS_2m_8.ss11 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=11)
do_test(RS_2m_8.ss12 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=12)
do_test(RS_2m_8.ss13 		-codec=2 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=13)

#
#
endif(OF_USE_REED_SOLOMON_2_M_CODEC)


#
# PART 4: Traditional Reed-Solomon over GF(2^8) tests
#
if(OF_USE_REED_SOLOMON_CODEC)

do_test(RS_28.src1 		-codec=1 -rs_m=8 -seed=1 -tot_src=1 -tot_rep=23)
do_test(RS_28.src2 		-codec=1 -rs_m=8 -seed=1 -tot_src=2 -tot_rep=23)
do_test(RS_28.src3 		-codec=1 -rs_m=8 -seed=1 -tot_src=3 -tot_rep=23)
do_test(RS_28.src4 		-codec=1 -rs_m=8 -seed=1 -tot_src=4 -tot_rep=23)
do_test(RS_28.src11 		-codec=1 -rs_m=8 -seed=1 -tot_src=11 -tot_rep=23)
do_test(RS_28.src13 		-codec=1 -rs_m=8 -seed=1 -tot_src=13 -tot_rep=23)
do_test(RS_28.src15 		-codec=1 -rs_m=8 -seed=1 -tot_src=15 -tot_rep=23)
do_test(RS_28.src17 		-codec=1 -rs_m=8 -seed=1 -tot_src=17 -tot_rep=23)
do_test(RS_28.src21 		-codec=1 -rs_m=8 -seed=1 -tot_src=21 -tot_rep=23)

do_test(RS_28.cr2.3.tx0 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500)
do_test(RS_28.cr1.2.tx1 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=1)
do_test(RS_28.cr1.2.tx2 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1000 -tx_type=2)
do_test(RS_28.cr1.2.tx3 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1090 -tx_type=3)
do_test(RS_28.cr2.3.tx4 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=4)
do_test(RS_28.cr2.3.tx5 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=5)
do_test(RS_28.cr2.3.tx6 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=6)
do_test(RS_28.cr2.3.tx7 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -tx_type=7)
do_test(RS_28.cr2.3.loss1 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -loss=2:20)
do_test(RS_28.cr2.3.loss2 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -loss=3:400)
do_test(RS_28.cr2.3.loss3 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=500 -loss=1)
do_test(RS_28.cr1.2.loss4 	-codec=1 -rs_m=8 -seed=1 -tot_src=1000 -tot_rep=1000 -loss=4)
do_test(RS_28.cr2.3.big 	-codec=1 -rs_m=8 -seed=1 -tot_src=10000 -tot_rep=5000)
do_test(RS_28.cr3.4.tx4 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=4)
do_test(RS_28.cr3.4.tx5 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=5)
do_test(RS_28.cr3.4.tx6 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=6)
do_test(RS_28.cr3.4.tx7 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -tx_type=7)
do_test(RS_28.cr3.4.loss1 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -loss=2:20)
do_test(RS_28.cr3.4.loss2 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -loss=3:380)
do_test(RS_28.cr3.4.loss3 	-codec=1 -rs_m=8 -seed=1 -tot_src=1500 -tot_rep=500 -loss=1)
do_test(RS_28.cr3.4.big 	-codec=1 -rs_m=8 -seed=1 -tot_src=15000 -tot_rep=5000)

do_test(RS_28.ss1 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=1)
do_test(RS_28.ss2 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=2)
do_test(RS_28.ss3 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=3)
do_test(RS_28.ss4 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=4)
do_test(RS_28.ss5 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=5)
do_test(RS_28.ss6 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=6)
do_test(RS_28.ss7 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=7)
do_test(RS_28.ss8 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=8)
do_test(RS_28.ss9	 	-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=9)
do_test(RS_28.ss10 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=10)
do_test(RS_28.ss11 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=11)
do_test(RS_28.ss12 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=12)
do_test(RS_28.ss13 		-codec=1 -rs_m=8 -seed=1 -tot_src=100 -tot_rep=100 -symb_sz=13)

#
#
endif(OF_USE_REED_SOLOMON_CODEC)
