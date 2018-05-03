
var map = L.map( 'map', {
    center: [ 34.0933, -118.340 ],
    zoom: 13
} );

L.tileLayer( 'https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={accessToken}', {
    attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://mapbox.com">Mapbox</a>',
    maxZoom: 18,
    id: 'mapbox.streets',
    accessToken: 'pk.eyJ1IjoicnlhbmJlZXpsZSIsImEiOiJ4VkRUVjBjIn0.craTzHuB402M6UDI3pLYCg'
} ).addTo( map );

var markers = [];

var updateMarkers = function() {

  var bounds = map.getBounds();
  var center = map.getCenter();

  var y = center.lat;
  var x = center.lng;
  var hSize = bounds.getNorthEast().lat - bounds.getSouthWest().lat;
  var vSize = bounds.getNorthEast().lng - bounds.getSouthWest().lng;
  var halfSize = Math.max( hSize, vSize ) / 2;

  var url = 'http://localhost:8080/region?origin=' + x + ',' + y + '&halfSize=' + halfSize;

  fetch( url, {
    method: 'GET',
    headers: {
      'Content-Type': 'application/json'
    }
  } )
  .then( function( res ) {
    return res.json();
  } )
  .then( function( res ) {

    console.log( 'res: ', res );

    markers.forEach( function( m ) {
      m.remove();
    } );

    ( res.items || [] ).forEach( function( item ) {

      var m = L.marker( [ item.y, item.x ] );
      markers.push( m );
      m.addTo( map );

    } );

  } )
  .catch( function( err ) {
    console.log( 'err: ', err );
  } )
  ;

};

updateMarkers();

map.on( 'dragend', updateMarkers );
map.on( 'zoom', updateMarkers );