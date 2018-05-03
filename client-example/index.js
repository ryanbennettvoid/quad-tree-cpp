
const PORT = process.env.PORT || 8080;

const Promise = require( 'bluebird' );
const Log = require( 'log' ), log = new Log();
const express = require( 'express' ), app = express();
const morgan = require( 'morgan' );
const bodyParser = require( 'body-parser' );
const rpc = require( 'dead-simple-rpc' );
const importer = require( './importer.js' );

const client = rpc.Client( {
  host: 'localhost',
  port: 9999
} );

importer.getItems()
.then( ( items ) => {

  log.debug( `inserting ${items.length} items` );

  return Promise.map( items, ( item ) => {

    const { lat, lng } = item;

    return client.evoke( 'insert', {
      originX: lng,
      originY: lat
    } );

  }, { concurrency: 100 } )
  ;

} )
.then( ( items ) => {
  return startServer();
} );

const startServer = () => {

  app.use( morgan( 'tiny' ) );
  app.use( bodyParser.json( { limit: '50mb'} ) );
  app.use( bodyParser.urlencoded( { limit: '50mb', extended: true } ) );

  app.get( '/', ( req, res ) => {
    res.json( { msg: 'ok' } );
  } );

  app.get( '/region', ( req, res ) => {

    const { origin, halfSize } = req.query;

    const [ lat, lng ] = origin.split( ',' );

    const q = {
      origin: {
        x: parseFloat( lng ),
        y: parseFloat( lat )
      },
      halfSize: parseFloat( halfSize )
    };

    log.debug( q );

    client.evoke( 'queryRange', q )
    .then( ( response ) => {
      log.debug( 'response: ', response );
      res.json( response );
    } )
    .catch( ( err ) => {
      log.error( 'err: ', err );
      res.status( 500 ).json( {} );
    } )
    ;

  } );

  app.listen( 8080, () => console.log( `listening on port ${PORT}...` ) );

};