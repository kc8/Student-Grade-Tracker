.PHONY: clean All

All:
	@echo "----------Building project:[ Cooper_finalExam - Debug ]----------"
	@cd "Cooper_finalExam" && "$(MAKE)" -f  "Cooper_finalExam.mk"
clean:
	@echo "----------Cleaning project:[ Cooper_finalExam - Debug ]----------"
	@cd "Cooper_finalExam" && "$(MAKE)" -f  "Cooper_finalExam.mk" clean
