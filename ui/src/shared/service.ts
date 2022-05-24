import { ErrorHandler, Injectable } from "@angular/core";

@Injectable()
export class Service implements ErrorHandler {
    handleError(error: any): void {
        throw new Error("Method not implemented.");
    }

    public connectToWebsocket(methodString: string) {
        return new Promise((resolve, reject) => {
            if ("WebSocket" in window) {
                var ws = new WebSocket("ws://localhost:8001/");
                let chartData;

                ws.onopen = function () {
                    console.log("Opening a connection...");
                    ws.send(JSON.stringify({ "method": methodString }))
                };
                ws.onmessage = function (event) {
                    console.log("response", JSON.parse(event.data))
                    chartData = JSON.parse(event.data)
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
    timestamp: [],
    humidity: [],
    temperature: [],
    relay: [] // set internally
}