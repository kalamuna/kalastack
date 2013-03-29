/**
 * 
 * Makes sure nginx is running
 * 
 */
class nginx::service {

	service { "nginx":
		ensure 		=> running,
		require 	=> Class["nginx::install"],
	}

}