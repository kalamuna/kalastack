
class nginx::install {
	
	package { "nginx":
		ensure => installed,
	}
	
}