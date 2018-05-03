
const PORT = process.env.PORT || 8080;

const Promise = require( 'bluebird' );
const Log = require( 'log' ), log = new Log();
const express = require( 'express' ), app = express();
const morgan = require( 'morgan' );
const bodyParser = require( 'body-parser' );
const Client = require( './lib/client.js' );
const importer = require( './importer.js' );

const client = Client( {
  host: 'localhost',
  port: 9999
} );

app.use( morgan( 'tiny' ) );
app.use( bodyParser.json( { limit: '50mb'} ) );
app.use( bodyParser.urlencoded( { limit: '50mb', extended: true } ) );
app.use( express.static( './public' ) );

app.get( '/region', ( req, res ) => {

  const { origin, halfSize } = req.query;

  const [ lng, lat ] = origin.split( ',' );

  const q = {
    origin: {
      x: parseFloat( lng ),
      y: parseFloat( lat )
    },
    halfSize: parseFloat( halfSize )
  };

  client.evoke( 'queryRange', q )
  .then( ( response ) => {
    res.json( response );
  } )
  .catch( ( err ) => {
    log.error( 'err: ', err );
    res.status( 500 ).json( {} );
  } )
  ;

} );

app.listen( 8080, () => {

  console.log( `listening on port ${PORT}...` );

  client.evoke( 'queryRange', {
    origin: { x: 0, y: 0 },
    halfSize: 180
  } )
  .then( ( response ) => {
    const { items } = response || {};
    if ( !items || items.length === 0 ) return loadItems();
  } )
  .catch( ( err ) => {
    log.error( 'err: ', err );
  } )
  ;

} );

const loadItems = () => {

  return importer.getItems()
  .then( ( items ) => {

    log.debug( `inserting ${items.length} items` );

    return Promise.map( items, ( item ) => {

      const { lat, lng, data } = item;

      return client.evoke( 'insert', {
        originX: lng,
        originY: lat,
        data
      } );

    }, { concurrency: 100 } )
    ;

  } )
  ;

};