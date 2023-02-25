class Page
{
	private:
		char * page_mem_storage = NULL;
		char input[INPUT_BUFFER];
		int input_len = 0;
		bool save_input;
		bool stop_loop_here;
		bool is_making_new_page;
		bool is_opening_page;
		bool is_removing_page;
		
		void input_commands();
		void save_input_to_memory();
		void output();
		void write();
		void get_input_for_opening_pages();
		void process_input();
	public:
		char * page_num = NULL;

		void print_help();
		void edit();
};

