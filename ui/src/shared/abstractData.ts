import { Directive } from "@angular/core";
import { ReceiveDataResponse, Service } from "./service";

@Directive()
export abstract class AbstractData {
    chartData: ReceiveDataResponse;
    constructor(
        public service: Service
    ) { }

    ngOnInit(): void {
        this.service.connectToWebsocket({ method: "receiveData" }).then((chartData) => {
            this.chartData = chartData as ReceiveDataResponse;
        }).finally(() => {
            this.createChart(this.chartData)
        })
    }

    protected abstract createChart(chartData: ReceiveDataResponse): void
}