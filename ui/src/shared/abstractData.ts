import { Directive } from "@angular/core";
import { ReceiveDataResponse, Service } from "./service";
import { QueryHistoricDataRequest } from "./request/QueryHistoricData";

@Directive()
export abstract class AbstractData {
    chartData: ReceiveDataResponse;
    constructor(
        public service: Service
    ) { }

    ngOnInit(): void {
        let now = new Date();
        // this.service.connectToWebsocket(new QueryHistoricDataRequest(now, now )).then((chartData) => {
        //     this.chartData = chartData as ReceiveDataResponse;
        // }).finally(() => {
        //     this.createChart(this.chartData)
        // })
    }

    protected abstract createChart(chartData: ReceiveDataResponse): void
}