
class nginx::install {
	
	package { "nginx":
		ensure => "1.1.19-1",
	}
	
}