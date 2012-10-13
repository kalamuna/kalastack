/**
 * 
 * Installs solr and tomcat
 * 
 */
class solr::install {
  package { "solr-tomcat":
    ensure  => "1.4.1+dfsg1-2ubuntu2",
    require => [
    	Class["phpfpm"],
    	Class["nginx"],
    ]
  }
}