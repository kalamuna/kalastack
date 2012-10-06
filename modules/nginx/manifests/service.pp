
class nginx::service ($ensure = "running") {

	service { "nginx":
		ensure 		=> $ensure,
		require 	=> Class["nginx::install"],
	}

}