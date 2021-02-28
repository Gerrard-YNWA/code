grpc reflect use grpcurl
### list
```
$ grpcurl --plaintext localhost:10000 list
grpc.reflection.v1alpha.ServerReflection
routeguide.RouteGuide
```

### describe service
```
$ grpcurl --plaintext localhost:10000 describe routeguide.RouteGuide
routeguide.RouteGuide is a service:
service RouteGuide {
  rpc GetFeature ( .routeguide.Point ) returns ( .routeguide.Feature );
  rpc ListFeatures ( .routeguide.Rectangle ) returns ( stream .routeguide.Feature );
  rpc RecordRoute ( stream .routeguide.Point ) returns ( .routeguide.RouteSummary );
  rpc RouteChat ( stream .routeguide.RouteNote ) returns ( stream .routeguide.RouteNote );
}
```

### describe info
```
$ grpcurl --plaintext localhost:10000 describe routeguide.Point
routeguide.Point is a message:
message Point {
  int32 latitude = 1;
  int32 longitude = 2;
}
```

### invoke 
```
$ grpcurl --plaintext -d '{"latitude":409146138, "longitude":-746188906}' localhost:10000 routeguide.RouteGuide/GetFeature
{
  "name": "Berkshire Valley Management Area Trail, Jefferson, NJ, USA",
  "location": {
    "latitude": 409146138,
    "longitude": -746188906
  }
}
```
