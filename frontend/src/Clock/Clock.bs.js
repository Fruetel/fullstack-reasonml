'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function Clock(Props) {
  var match = React.useState((function () {
          return /* LoadingTime */0;
        }));
  var setState = match[1];
  var state = match[0];
  fetch("http://127.0.0.1:333").then((function (response) {
              return response.json();
            })).then((function (jsonResponse) {
            Curry._1(setState, (function (_previousState) {
                    return /* LoadedTime */[jsonResponse.time];
                  }));
            console.log(state);
            return Promise.resolve(/* () */0);
          })).catch((function (_err) {
          Curry._1(setState, (function (_previousState) {
                  return /* ErrorFetchingTime */1;
                }));
          return Promise.resolve(/* () */0);
        }));
  return React.createElement("div", {
              style: {
                display: "flex",
                height: "120px",
                alignItems: "center",
                justifyContent: "center"
              }
            }, typeof state === "number" ? (
                state !== 0 ? "An error occurred" : "Loading..."
              ) : "Time: " + (String(state[0]) + ""));
}

var make = Clock;

exports.make = make;
/* react Not a pure module */
