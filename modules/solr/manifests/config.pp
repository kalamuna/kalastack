/**
 * 
 * Class that governs the config of the solr server
 * 
 */
class solr::config {
  
  solr::schema { "schema.xml": 
    path => "/etc/solr/conf/schema.xml",
    require => Class["solr::install"],
    notify => Class["solr::service"],
  } 
  
  solr::solrconfig { "solrconfig.xml": 
    path => "/etc/solr/conf/solrconfig.xml",
    require => Class["solr::install"],
    notify => Class["solr::service"],
  }
  
  solr::server { "server.xml": 
    path => "/etc/tomcat6/server.xml",
    port => 8983,
    require => Class["solr::install"],
    notify => Class["solr::service"],
  }

}