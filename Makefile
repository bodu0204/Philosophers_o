PROJECT_NAME	= Philosophers
ACHIEV			= philo
ACHIEVtest		= $(ACHIEV).test
ACHIEVb			= $(ACHIEV)_bonus
ACHIEVtest		= $(ACHIEV).test
SRC_PASS		= philo
SRCb_PASS		= philo_bonus
OTHER_PASS		= other
SUBMIT_d		= $(PROJECT_NAME)/
TEST_d			= test_case_0/

all : $(ACHIEV)

$(ACHIEV) : file
	cd "$(SUBMIT_d)$(ACHIEV)" && make all
	cp -f $(SUBMIT_d)$(ACHIEV)/$(ACHIEV) ./$(ACHIEVtest)

bonus : $(ACHIEVb)

$(ACHIEVb) : file
	cd "$(SUBMIT_d)$(ACHIEVb)" && make all
	cp -f $(SUBMIT_d)$(ACHIEVb)/$(ACHIEVb) ./

push : fclean
	git add .
	git commit --allow-empty -m "commit form makefile"
	git push

submitfile : push file

submit : outclean submitfile
	mv $(SUBMIT_d) ../

file : fclean 
	mkdir $(SUBMIT_d)
	cp -rf $(SRC_PASS) $(SUBMIT_d)
	cp -rf $(SRCb_PASS) $(SUBMIT_d)

test : all bonus
	mkdir $(TEST_d)
	cp -f $(SUBMIT_d)$(ACHIEV) $(TEST_d)
	cp -f $(SUBMIT_d)$(ACHIEVb) $(TEST_d)

fclean :
	rm -rf $(SUBMIT_d)
	rm -rf $(TEST_d)
	rm -f $(ACHIEVtest)
	rm -f $(ACHIEVbtest)

outclean :
	rm -rf ../$(SUBMIT_d)

allclean : fclean outclean

re : fclean all
