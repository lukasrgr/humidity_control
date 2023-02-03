import { NumberSymbol } from "@angular/common";
import { ErrorHandler, Injectable } from "@angular/core";
import { BehaviorSubject } from "rxjs";
import { JsonRpcRequest } from "./request/jsonrpc";
import { GetLatestDataRequest } from "./request/GetLatestData";
import { endOfDay, startOfDay } from "date-fns";

@Injectable()
export class Service {

    public latestData: BehaviorSubject<{ humidity: number, temperature: number, timestamp: string, relay: number }> = new BehaviorSubject({
        humidity: 0, temperature: 0, timestamp: "", relay: 0
    });

    public historyPeriod: { fromDate: Date, toDate: Date } = { fromDate: startOfDay(new Date()), toDate: endOfDay(new Date()) }

    constructor() {
        const FIVE_MIN = 1000 * 60 * 5;
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
        let msToNextRounded5Min = FIVE_MIN - (Date.now() % FIVE_MIN) + 10000
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
        }, msToNextRounded5Min, () => msToNextRounded5Min = FIVE_MIN - (Date.now() % FIVE_MIN) + 10000)
    }

    public connectToWebsocket(request: JsonRpcRequest) {
        return new Promise((resolve, reject) => {
            if ("WebSocket" in window) {
                var ws = new WebSocket("ws://192.168.178.107:8001/");
                ws.onopen = function () {
                    console.log("request", request);
                    ws.send(JSON.stringify(request))
                };
                ws.onmessage = function (event) {
                    console.log("response", JSON.parse(event.data))
                    let chartData = JSON.parse(event.data)
                    resolve(chartData);
                }
            }
        })
    }
}

export type ReceiveDataResponse = {
    timestamp: string[],
    humidity: number[],
    temperature: number[],
    relay: number[] // set internally
}