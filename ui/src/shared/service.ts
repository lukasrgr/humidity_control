import { NumberSymbol } from "@angular/common";
import { ErrorHandler, Injectable } from "@angular/core";
import { BehaviorSubject } from "rxjs";
import { JsonRpcRequest } from "./request/jsonrpc";
import { GetLatestDataRequest } from "./request/GetLatestData";

@Injectable()
export class Service implements ErrorHandler {

    public latestData: BehaviorSubject<{ humidity: number, temperature: number, timestamp: string, relay: number }> = new BehaviorSubject({
        humidity: 0, temperature: 0, timestamp: "", relay: 0
    });
    handleError(error: any): void {
        throw new Error("Method not implemented.");
    }

    constructor() {
        this.connectToWebsocket(new GetLatestDataRequest())
            .then(data => {
                let response = (data as ReceiveDataResponse)
                this.latestData.next({
                    humidity: response.humidity[0],
                    temperature: response.temperature[0],
                    timestamp: response.timestamp[0],
                    relay: response.relay[0]
                })
            })
        setInterval(() => {
            this.connectToWebsocket(new GetLatestDataRequest())
                .then(data => {
                    let response = (data as ReceiveDataResponse)
                    this.latestData.next({
                        humidity: response.humidity[0],
                        temperature: response.temperature[0],
                        timestamp: response.timestamp[0],
                        relay: response.relay[0]
                    })
                })
        }, 300000)
    }

    public connectToWebsocket(request: JsonRpcRequest) {
        return new Promise((resolve, reject) => {
            if ("WebSocket" in window) {
                var ws = new WebSocket("ws://192.168.178.107:8001/");
                ws.onopen = function () {
                    console.log("Opening a connection...", request);
                    ws.send(JSON.stringify(request))
                };
                ws.onmessage = function (event) {
                    console.log("how is data looking", event.data)
                    console.log("response", JSON.parse(event.data))
                    let chartData = JSON.parse(event.data)
                    resolve(chartData);
                }
            }
        })
    }
}

export const EMPTY_DATASET = [{
    label: "no Data available",
    data: [],
    hidden: false
}];

export type ReceiveDataResponse = {
    timestamp: string[],
    humidity: number[],
    temperature: number[],
    relay: number[] // set internally
}